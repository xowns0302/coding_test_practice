
var resultMap = new Map();
var transCompSize = 0;
var param = new Map();
importPackage(Packages.emro.util);
importPackage(Packages.volcano.custom.interfacemodule);
var util = new SHA512Util();
var reject_cause = ""; //반려사유
var temp = new Map();
var send_yes = ""; //업체SMS대상 확인
var exmld = $xmlManager.getDescriptor("properties");
var sms_send_no = exmld.getDescriptorElement("sms.send.no").getText();
var serverPath = exmld.getDescriptorElement("server.url").getText();    //메일  JSP 참조하기 위한 URL(WAS)
var webserverPath = exmld.getDescriptorElement("webserver.url").getText(); //메일 image URL(외부웹서버)
var email_send_nm = exmld.getDescriptorElement("email.send.nm").getText(); //메일 수신자명(세션값 없는경우)
var email_send_ad = exmld.getDescriptorElement("email.send.ad").getText(); //메일 수신자 메일주소(세션값 없는경우)

//거래처 승인내역 이관 대상 조회
var paramList = $jdbc.queryList("common/interface", "renewal.select.eai_mdm_vd_app", null);

for (var i = 0; i < paramList.size(); i++) {
    var paramMap = $jdbc.query("common/interface", "renewal.select.eai_mdm_vd_app.map", paramList.get(i));

    try {

        if (paramMap.aprval_stat_cd == "30") {
            //거래처 승인내역 이관 처리1 - ESPTEPB merge
            $jdbc.update("common/interface", "renewal.merge.esptepb", paramMap);
        }

        //거래처 승인내역 이관 처리 후처리 = EAI_MDM_VD_APP trans_yn = 'Y'
        $jdbc.update("common/interface", "renewal.update.eai_mdm_vd_app", paramMap);

        //업체거래상태변경로직추가
        //1.paramList오브젝트에 TRNSC_PS_YN = 'Y'인 경우에만 ESMVDHT히스토리테이블에 INSERT 처리
        // apros에서 관리하는 업체애 대해서 처리
        if ((paramMap.vd_sn != null && paramMap.vd_sn != "") && paramMap.trnsc_ps_yn == "Y") {
            var vdInfo = $jdbc.query("esourcing/sql-vendor", "select.vd.using.biz.reg.no", paramMap);
            $jdbc.update("esourcing/sql-vendor", "insert.vd.deal.sts.history", vdInfo);
        }
        System.out.println("=====> " + paramMap);
        //신규거래처 승인인 경우
        if ((paramMap.vd_sn != null && paramMap.vd_sn != "") && paramMap.new_vd_cd_yn == "Y") {

            if (paramMap.aprval_stat_cd != "30") {
                //업체반려시
                $jdbc.update("stdm/stdm", "save.new.reject.list", paramMap);

                try {
                    reject_cause = paramMap.givback_rsn;
                    var brno = paramMap.brno;
                    var actcust_nm = paramMap.actcust_nm;

                    var userinfos = $jdbc.queryList("stdm/stdm", "get.latest.send.userinfo.eai.mdm.vd.req", paramMap);

                    var mailContents = "";
                    var comp_cd = "10";

                    var mailParam = new Map();
                    mailParam.put("sys_id", "EMRO");
                    mailParam.put("mail_tmp_id", "T25");
                    mailParam.put("comp_cd", comp_cd);
                    mailParam.put("comp_cd_yn", "N");
                    mailParam.put("mail_type", "B");

                    mailContents = $jdbc.query("admin/template", "select.mail.template.info", mailParam);

                    var snd_title = "";
                    var snd_subject = "";

                    if (mailContents) {
                        snd_title = mailContents.snd_title;
                        snd_subject = mailContents.snd_subject;

                        snd_subject = snd_subject.replace('%reject_cause%', reject_cause);
                        snd_subject = snd_subject.replace('%brno%', brno);
                        snd_subject = snd_subject.replace('%actcust_nm%', actcust_nm);
                    }

                    if (mailContents && mailContents.use_yn == "Y") {
                        for (var z = 0; z < userinfos.size(); z++) {
                            var mail = new Map();
                            mail.from = userinfos.get(z).chr_email;
                            mail.fromName = userinfos.get(z).chr_nm;
                            mail.to = userinfos.get(z).chr_email;
                            mail.toName = userinfos.get(z).chr_nm;
                            mail.snd_title = snd_title;
                            mail.snd_subject = snd_subject;
                            mail.url = serverPath + "/mail/templateMail.jsp";
                            mail.image_url = webserverPath + "/mail/img/";
                            mail.sys_id = mailParam.get("sys_id");
                            mail.comp_cd = mailParam.get("comp_cd");
                            mail.mail_type = mailParam.get("mail_type");

                            if (mail.to != "" && mail.to != null) {
                                $jdbc.update("admin/template", "insert.email", mail);
                            }
                        }
                    }
                } catch (mailErr) {
                    $logger.error("[MAIL][T25][NEW_REJECT] send fail. vd_sn=" + paramMap.vd_sn + " / err=" + mailErr);
                }

            } else {
                // 업체승인시
                // 임시->정식권한부여
                var send_yes = "Y"; //업체SMS대상 확인
                var biz_reg_no = paramMap.biz_reg_no;
                paramMap.usr_id = biz_reg_no;
                paramMap.role_cd = 'SMASTER';

                $jdbc.update("admin/user", "insert.user.role", paramMap);

                $jdbc.update("stdm/stdm", "save.new.accept.list", paramMap);

                // 강릉ERP 서울병원이 승인되었고 업체가 강릉병원도 요청하였다면 강릉병원에 승인처리
                if (paramMap.gn_mdm_targ_yn == "Y" && paramMap.new_gn_vd_cd_yn == "Y") {

                    var gn_inter = new InterfaceSendProvider();
                    var reqNo = $jdbc.query("common/interface", "select.reqno.info", null).req_no;

                    var param3 = new Map();
                    param3.vd_sn = paramMap.vd_sn;
                    param3.if_cd = "IF4022";
                    param3.if_typ = "GNERP";
                    param3.req_no = reqNo;
                    param3.req_mode = "I";
                    param3.auto_aprv_yn = "Y";
                    //신규업체요청정보 MDM전송
                    var result = gn_inter.sendInterface(param3);

                    var param4 = new Map();
                    param4.vd_sn = paramMap.vd_sn;
                    param4.if_cd = "IF4080";
                    param4.att_typ = "VDFILE";
                    param4.if_typ = "GNERP";
                    param4.req_no = reqNo;
                    param4.req_mode = "I";

                    //신규업체파일정보 MDM전송
                    var result2 = gn_inter.sendInterface(param4);
                }


                //AFIS 3.0 MDM 인터페이스 시작 ****************************************************
                var nSysCnt = $jdbc.query("common/interface", "renewal.select.list.n_sys_cnt", null);
                // AFIS 3.0 오픈을 했으면 AFIS3.0 과 I/F 함
                if (nSysCnt.get("n_sys_cnt") > 0) {
                    //importClass(Packages.volcano.custom.interfacemodule.InterfaceSendProvider);
                    var sendService = new InterfaceSendProvider();

                    var interfaceMap = new Map();
                    interfaceMap.put("if_cd", "IF1023");
                    interfaceMap.put("if_typ", "AFIS");
                    interfaceMap.put("vd_sn", paramMap.vd_sn);

                    sendService.sendInterface(interfaceMap);
                }
                //AFIS 3.0 MDM 인터페이스 종료 ****************************************************
            }

            //변경승인인 경우
        } else if ((paramMap.vd_sn != null && paramMap.vd_sn != "") && paramMap.eai_recv_side_task_typ_cd == "U") {

            if (paramMap.aprval_stat_cd != "30") {//업체반려시 류태준 추가
                //ESMVDGL 반려로 업데이트
                $jdbc.update("stdm/stdm", "save.new.reject.list", paramMap);

                try {
                    //공급업체 정보변경 요청건 반려
                    reject_cause = paramMap.givback_rsn;
                    var brno = paramMap.brno;
                    var actcust_nm = paramMap.actcust_nm;

                    //반려정보 저장
                    var userinfos = $jdbc.queryList("stdm/stdm", "get.latest.send.userinfo.eai.mdm.vd.req", paramMap); //eai_mdm_vd_req최근 건의 담당자로 설정

                    // 0. 메일전송
                    var mailContents = "";
                    var comp_cd = "10";

                    // 1. 메일 템플릿 정보를 가져온다.
                    var mailParam = new Map();
                    mailParam.put("sys_id", "EMRO");
                    mailParam.put("mail_tmp_id", "T25");   // 공급사 정보변경요청 반려
                    mailParam.put("comp_cd", comp_cd);
                    mailParam.put("comp_cd_yn", "N");      // 병원별 템플릿 동일
                    mailParam.put("mail_type", "B");

                    mailContents = $jdbc.query("admin/template", "select.mail.template.info", mailParam);

                    var snd_title = "";
                    var snd_subject = "";

                    ///////////////////////////////////////////////////////////////
                    // 2. EMAIL내용 준비
                    ///////////////////////////////////////////////////////////////

                    if (mailContents) {
                        snd_title = mailContents.snd_title;
                        snd_subject = mailContents.snd_subject;
                        snd_subject = snd_subject.replace('%reject_cause%', reject_cause);
                        snd_subject = snd_subject.replace('%brno%', brno);
                        snd_subject = snd_subject.replace('%actcust_nm%', actcust_nm);

                    }
                    if (mailContents) {
                        $data.mails = new List();
                        for (var z = 0; z < userinfos.size(); z++) {
                            var mail = new Map();
                            mail.from = userinfos.get(z).chr_email;
                            mail.fromName = userinfos.get(z).chr_nm;
                            mail.to = userinfos.get(z).chr_email;
                            mail.toName = userinfos.get(z).chr_nm;
                            mail.snd_title = snd_title;           //메일 제목
                            mail.snd_subject = snd_subject;         //메일 본문
                            mail.url = serverPath + "/mail/templateMail.jsp"; //공통메일 템플릿
                            mail.image_url = webserverPath + "/mail/img/";     //메일  JSP 참조하기 위한 URL(WAS)
                            mail.sys_id = mailParam.get("sys_id");
                            mail.comp_cd = mailParam.get("comp_cd");
                            mail.mail_type = mailParam.get("mail_type");

                            if (mail.to != "" && mail.to != null) {
                                $data.mails.add(mail);
                            }
                        }
                        $logger.info('size----------------' + $data.mails.size());
                        //발송여부가 'Y'인 경우만 이메일 발송
                        if (mailContents.use_yn == "Y") {
                            for (var y = 0; y < $data.mails.size(); y++) {
                                $data.mail = $data.mails[y];
                                $jdbc.update("admin/template", "insert.email", $data.mail);
                            }
                        }
                    }
                } catch (mailErr) {
                    $logger.error("[MAIL][T25][REJECT] send fail. vd_sn=" + paramMap.vd_sn + " / err=" + mailErr);
                }
            } else {
                //업체승인시
                //거래처 승인내역 이관 처리2 - ESMVDGL update(RQ)
                $jdbc.update("common/interface", "renewal.update.esmvdgl", paramMap);

                //승인정보 업데이트
                $jdbc.update("esourcing/sql-vendor", "aprove.vd.chg.info", paramMap);


                // 강릉ERP 서울병원이 승인되었고 업체가 강릉병원도 요청하였다면 강릉병원에 요청
                if (paramMap.gn_mdm_targ_yn == "Y" && paramMap.new_gn_vd_cd_yn == "N") {
                    //importPackage(Packages.volcano.custom.interfacemodule);
                    var gn_inter = new InterfaceSendProvider();

                    var reqNo = $jdbc.query("common/interface", "select.reqno.info", null).req_no;

                    var param3 = new Map();
                    param3.vd_sn = paramMap.vd_sn;
                    param3.if_cd = "IF4022";
                    param3.if_typ = "GNERP";
                    param3.req_no = reqNo;
                    param3.req_mode = "U";
                    param3.auto_aprv_yn = "Y";
                    //신규업체요청정보 MDM전송
                    var result = gn_inter.sendInterface(param3);

                    var param4 = new Map();
                    param4.vd_sn = paramMap.vd_sn;
                    param4.if_cd = "IF4080";
                    param4.att_typ = "VDFILE";
                    param4.if_typ = "GNERP";
                    param4.req_no = reqNo;
                    param4.req_mode = "U";

                    //신규업체파일정보 MDM전송
                    var result2 = gn_inter.sendInterface(param4);
                }


                //AFIS 3.0 MDM 인터페이스 시작 ****************************************************
                var nSysCnt = $jdbc.query("common/interface", "renewal.select.list.n_sys_cnt", null);
                // AFIS 3.0 오픈을 했으면 AFIS3.0 과 I/F 함
                if (nSysCnt.get("n_sys_cnt") > 0) {

                    //importClass(Packages.volcano.custom.interfacemodule.InterfaceSendProvider);
                    var sendService = new InterfaceSendProvider();

                    var interfaceMap = new Map();
                    interfaceMap.put("if_cd", "IF1023");
                    interfaceMap.put("if_typ", "AFIS");
                    interfaceMap.put("vd_sn", paramMap.vd_sn);

                    sendService.sendInterface(interfaceMap);
                }
                //AFIS 3.0 MDM 인터페이스 종료 ****************************************************

                //기준정보로 승인요청된것만 알림처리(서울승인요청(SO_MDM_CHK_RES_CD가 P) 또는 강릉승인요청(GN_MDM_CHK_RES_CD가 P인) 경우
                if ((paramMap.SO_MDM_CHK_RES_CD == "P") || (paramMap.GN_MDM_CHK_RES_CD == "P")) {
                    //SMS 받을 대상 목록(업체 담당자들) 조회
                    var send_yes = $jdbc.queryList("login", "vendor_aprov_yn", paramMap);
                    if (send_yes == "Y") {
                        var userinfos = $jdbc.queryList("login", "external.valid.usr.list", paramMap);

                        var udpClient = new UDPClient();
                        var smsMap = new Map();

                        smsMap.sms_tmp_id = "S09";
                        smsMap.sys_id = param.sys_id;

                        var sendMessage = $jdbc.query("admin/template", "select.sms.template.info", smsMap);
                        smsMap.message = sendMessage.conts;
                        smsMap.send_no = sms_send_no;
                        smsMap.usr_id = 'APROS';
                        smsMap.comp_cd = '00';
                        var ret_val = '';
                        for (var j = 0; j < userinfos.size(); j++) {
                            smsMap.send_dt = userinfos.get(j).sms_send_dt;
                            smsMap.receive_no = userinfos.get(j).chr_mobile;
                            if (smsMap.receive_no != "" && smsMap.receive_no != null) {
                                if (sendMessage.use_yn == "Y") {
                                    ret_val = udpClient.sendToSMS(smsMap);
                                }
                            }
                        }

                        // 0. 메일전송
                        var comp_cd = "10";
                        var mailContents = "";

                        // 1. 메일 템플릿 정보를 가져온다.
                        param.comp_cd = comp_cd;
                        param.comp_cd_yn = 'N';    // 병원별 템플릿이 동일 할 경우는 'N'
                        param.mail_tmp_id = 'T17';  // 공급사 정보변경요청 승인

                        mailContents = $jdbc.query("admin/template", "select.mail.template.info", param);

                        var snd_title = "";
                        var snd_subject = "";

                        ///////////////////////////////////////////////////////////////
                        // 2. EMAIL내용 준비
                        ///////////////////////////////////////////////////////////////

                        if (mailContents) {
                            snd_title = mailContents.snd_title;
                            snd_subject = mailContents.snd_subject;
                        }
                        if (mailContents) {
                            $data.mails = new List();
                            for (var z = 0; z < userinfos.size(); z++) {
                                var mail = new Map();
                                mail.from = email_send_ad;
                                mail.fromName = email_send_nm;
                                mail.to = userinfos.get(z).chr_email;
                                mail.toName = userinfos.get(z).chr_nm;
                                mail.snd_title = snd_title;           //메일 제목
                                mail.snd_subject = snd_subject;         //메일 본문
                                mail.url = serverPath + "/mail/templateMail.jsp"; //공통메일 템플릿
                                mail.image_url = webserverPath + "/mail/img/";     //메일  JSP 참조하기 위한 URL(WAS)
                                mail.comp_cd = comp_cd;  //병원별 메일 템플릿 구분자

                                if (mail.to != "" && mail.to != null) {
                                    $data.mails.add(mail);
                                }
                            }
                            $logger.info('size----------------' + $data.mails.size());
                            //발송여부가 'Y'인 경우만 이메일 발송
                            if (mailContents.use_yn == "Y") {
                                for (var y = 0; y < $data.mails.size(); y++) {
                                    $data.mail = $data.mails[y];
                                    $jdbc.update("admin/template", "insert.email", $data.mail);
                                }
                            }
                        }
                    }
                }
            }
        }
        resultMap.put("log_sts", "SUCCESS");
        resultMap.put("err_msg", "");

    }
    catch (e) {
        var err = e.toString();
        var ora_err = err.substring(err.indexOf("ORA"), err.length);
        rtrn_msg = "처리시 에러가 발생을 하였습니다." + "\n" + "에러내용" + " : " + ora_err;
        resultMap.put("log_sts", "FAIL");
        resultMap.put("err_msg", rtrn_msg);
    }

    //인터페이스(EAI_MDM*->업무테이블) 로그 추가
    var dt = new Date();
    var today = dt.getFullYear() + ((dt.getMonth() + 1).toString() < 10 ? ("0" + (dt.getMonth() + 1)).toString() : (dt.getMonth() + 1).toString()) + (dt.getDate() < 10 ? ("0" + dt.getDate()).toString() : dt.getDate().toString());
    resultMap.tx_id = today + Math.floor(Math.random() * 99999999);
    resultMap.job_key = "{ vd_sn : '" + paramMap.vd_sn + "'}";
    if (paramList.size() == 0) {
        resultMap.req_data = "";
    } else {
        resultMap.req_data = paramList.get(i).toString();
    }
    resultMap.res_data = "";
    resultMap.if_nm = "거래처승인내역";
    resultMap.if_cd = "IF1019";

    $logger.info("## resultMap:" + resultMap);
    //$jdbc.update("common/interface","merge.interface.send.log", resultMap);
    $jdbc.update("common/interface", "merge.interface.send.log.insert", resultMap);

}
#회의실 예약
#09시부터 18시까지 예약가능
#시간 단위로만 예약 가능
#같은 회의실을 사용하는 시간은 겹칠 수 없다
#길이가 0인 회의 즉, 시작 종료시간이 같은 회의는 예약안됨
#회의가끝나는 시간에 다른회의가 시작하는건 가능

n,m = map(int, input().split())
room = {}
for i in range(n):
    name = input()
    room[name]=[0]*18

for i in range(m):
    name, start, end = input().split()
    start = int(start)
    end = int(end)
    for j in range(start, end):
        room[name][j] = 1

room = sorted(room.items())#여기서 dictionary-> list로 변경됨

#리스트로 변경했기때문에 인덱스 i == name이고 name 의 두번째 배열에 값이
#1에서 0으로 바뀌면 시작 시간을 기록 0에서 1로 바뀌면 끝나는 시간을 기록함
for i in range(n):
    current = 1
    temp = []
    for j in range(9,18):
        if current == 1 and room[i][1][j] == 0:
            sTime = j
            current =0
        elif current == 0 and room[i][1][j] == 1:
            fTime = j
            current =1  
            temp.append([sTime,fTime])
    if current ==0:#끝까지 0으로 됐으면 1로 바뀐게 아니라 비어있는 경우만 따로 기록
        temp.append([sTime,18])
    print(f'Room {room[i][0]}:')
    if len(temp)==0:
        print('Not available')
    else:
        print(f'{len(temp)} available:')
        for k in range(len(temp)):
            print(f'{temp[k][0]:02d}-{temp[k][1]}')

    print('-----')
    
        
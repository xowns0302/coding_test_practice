#바로 옆에 앉을 수 없고 대각선 허용
#좌석의 안전도 == 가장 가까운 좌석과의 거리
#모든 자리가 비어있으면 (1,1)
#식사는 한 번만(사번으로 구분)
n,m,q = map(int, input().split())
ID = [0]*(10**4+1) # 0: not in, 1: Out, [x,y]: 배정자리
table =[[0]*(m+2)for _ in range(n+2)]# +2를 해서 범위 밖 테이블도 0으로 초기화

#가장 가까운 점과의 거리를 반환하는 함수
#전체 테이블을 돌면서 거리 최솟값을 반환함
def nearest(x,y):
    minD = 1000
    for i in range(1, n+1):
        for j in range(1,m+1):
            if(table[i][j]):
                d = (x-i)*(x-i) + (y-j)*(y-j)
                if d<minD:
                    minD = d
    return minD

#table에 사람을 앉히고 기록하는 함수
#table을 돌면서 안전도가 가장 높은 자리에 착석
#앉힌 좌표에 1 세팅
def assign(pid):
    maxD = 0
    for i in range(1, n+1):
        for j in range(1,m+1):
            if table [i][j] == 0 and table[i-1][j]==0 and \
            table [i][j-1] == 0 and table [i+1][j] == 0 and table [i][j+1] == 0 :
                d = nearest(i,j)
                if d >maxD:
                    maxD = d
                    ID[pid]= [i,j]
    if maxD ==0:
        return False
    else:
        table[ID[pid][0]][ID[pid][1]] = 1
        return True
    
for i in range(q):
    inOut, pid = input().split()
    pid = int(pid)
    if inOut == 'In':
        if ID [pid] == 0:
            if assign(pid):
                print(f'{pid} gets the seat ({ID[pid][0]}, {ID[pid][1]}).')
            else:
                print('There are no more seats.')
        elif ID[pid]==1:
            print(f'{pid} already ate lunch.')
        else :
            print(f'{pid} already seated.')
    else : #Out {id}
        if ID[pid]==0:
            print(f"{pid} didn't eat lunch.")
        elif ID[pid]==1:
            print(f'{pid} already left seat.')
        else :
            print(f'{pid} leaves from the seat ({ID[pid][0]}, {ID[pid][1]}).')
            table[ID[pid][0]][ID[pid][1]] = 0
            ID[pid]=1
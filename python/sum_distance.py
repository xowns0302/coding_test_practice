#거리 합 구하기
#서브트리 사이즈를 구해서 서브트리 기준 인접 노드 까지의 거리 * 갯수를 기준 노드에 더해준다
#만약에 내 자식이 있으면 자식까지의 거리 * 자식의 서브트리 갯수 + 자식의 누적 거리 = 내 누적거리
#이유는 내가 자식까지 거리는 자식이 만들어내는 경우의 수만큼 더해지기때문이고


def dfs1(current, parent):
    subtreeSize[current] =1
    for i in range(len(node[current])):
        child = node[current][i][0]
        weight = node[current][i][1]
        if child != parent:
            dfs1(child, current)
            distSum[current] += distSum[child] + subtreeSize[child] * weight
            subtreeSize[current] += subtreeSize[child]#여기서 구한 값은 루트노드에서의 모든 거리합
            print(f'distSum[{current}]: {distSum[current]}')
            print('')
            print(f'현재 노드: {child} 서브트리사이즈: {subtreeSize[child]} weight: {weight}')
            print('')
    return

"""
멀어지는거 가까워지는거 구분해서 weight만큼 더해주면되는데
(멀어지는거 - 가까워지는거) * weight 
= (n - subtreeSize[child] - subtreeSize[child]) * weight
"""
def dfs2(current, parent):
    for i in range(len(node[current])):
        child = node[current][i][0]
        weight = node[current][i][1]
        if child != parent:
            distSum[child] = distSum[current] + weight * (n - 2 * subtreeSize[child]) 
            dfs2(child, current)
    return

n = int(input())
node = [[] for _ in range(n+1)]
subtreeSize =[0]*(n+1)
distSum = [0]*(n+1)

for i in range(n-1):
    x,y,t = map(int, input().split())
    node[x].append([y,t])
    node[y].append([x,t])

dfs1(1,1)
print(distSum)
dfs2(1,1)

print(node)
print(subtreeSize)
print(distSum)


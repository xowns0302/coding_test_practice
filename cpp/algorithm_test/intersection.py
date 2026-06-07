#교차로문제
#자신을 기준으로 오른쪽에 위치한 도로에 차량이 있으면 1초동안 출발하지 않고 차량이 없으면 통과
#도로 순서는 A -> D -> C -> B -> A 로 각 오른쪽에 있는 차량이라고 함
#4곳에 모두 차량이 있으면 교착 상태

import sys
input =sys.stdin.readline

def main():
    n = int(input())

    for i in range(n):
        anum, char = input().split()
        num = int(anum)
        print(num, char)

        



#!/usr/bin/python
# Created by Joao A. Jesus Jr. <joao29a@gmail.com>
#            Joao M. Velasques Faria

from collections import deque

class AStar:
    def distBetween(self,current,neighbor):
        pass

    def heuristicEstimate(self,start,goal):
        pass

    def neighborNodes(self,current):
        pass
    
    def reconstructPath(self,cameFrom,goal):
        path = deque()
        node = goal
        path.appendleft(node)
        while node in cameFrom:
            node = cameFrom[node]
            path.appendleft(node)
        return path
    
    def getLowest(self,openSet,fScore):
        lowest = float("inf")
        lowestNode = None
        for node in openSet:
            if fScore[node] < lowest:
                lowest = fScore[node]
                lowestNode = node
        return lowestNode

    def aStar(self,start,goal):
        cameFrom = {}
        openSet = set([start])
        closedSet = set()
        gScore = {}
        fScore = {}
        gScore[start] = 0
        fScore[start] = gScore[start] + self.heuristicEstimate(start,goal)
        while len(openSet) != 0:
            current = self.getLowest(openSet,fScore)
            if current == goal:
                return self.reconstructPath(cameFrom,goal)
            openSet.remove(current)
            closedSet.add(current)
            for neighbor in self.neighborNodes(current):
                tentative_gScore = gScore[current] + self.distBetween(current,neighbor)
                if neighbor in closedSet and tentative_gScore >= gScore[neighbor]:
                    continue
                if neighbor not in closedSet or tentative_gScore < gScore[neighbor]:
                    cameFrom[neighbor] = current
                    gScore[neighbor] = tentative_gScore
                    fScore[neighbor] = gScore[neighbor] + self.heuristicEstimate(neighbor,goal)
                    if neighbor not in openSet:
                        openSet.add(neighbor)
        return 0

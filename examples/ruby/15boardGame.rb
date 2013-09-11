
# Algorithm A*
# Devlopers: Vanderson M. Rosario <vandersonmr2@gmail.com>
# 	     Diogo T. Murata <diogomurata@gmail.com>
# This code is under MIT licence.
#
# board[4][4] being 1 a position ocupated and 0 for blank.
#	0 - blank
#	1 - Ocupated

load '../../libs/ruby/AlgorithmA.rb'  

def printBoard(board)
   puts ""
   board.each do |line|
      puts ""
      line.each do |item|
         print "| #{item} |"
      end
   end
   puts ""
end

def getBlankPosition(board)
   x = 0
   y = 0
   board.each do |line|
      y=0
      line.each do |item|
         if (item == 0)
            return x,y
         end
         y=y+1
      end
      x=x+1
   end
end

def distanceBetween(board1,board2)
   b1x,b1y = getBlankPosition(board1)
   b2x,b2y = getBlankPosition(board2)
   return (b1x-b2x).abs + (b1y-b2y).abs
end


# Euclidian distance
def distance(val1,x1,y1)
   x2=val1/4
   y2=val1.modulo(4)
   dist = Math.sqrt((x1 - x2)**2 + (y1 - y2)**2)
   return dist
end


def heuristicCostEstimate(current,goal)
   cost = 0
   (0..3).each do |i|
      (0..3).each do |j|
         cost += distance(goal[i][j],i,j)
      end
   end
   return cost
end

def valido?(x,y)
   return x >= 0 && y >= 0 && x<=3 && y<=3
end

def swapPosBoard(boardOld,x,y,newX,newY)
   board = Marshal.load( Marshal.dump(boardOld) )
   aux = board[newX][newY]
   board[newX][newY] = board[x][y]
   board[x][y] = aux
   return board
end

def neighborNodes(board)
   neighbors = []
   pos1,pos2 = getBlankPosition(board)
   if (valido?(pos1+1,pos2))
      neighbors.push(swapPosBoard(board,pos1,pos2,pos1+1,pos2))
   end
   if (valido?(pos1-1,pos2))
      neighbors.push(swapPosBoard(board,pos1,pos2,pos1-1,pos2))
   end
   if (valido?(pos1,pos2+1))
      neighbors.push(swapPosBoard(board,pos1,pos2,pos1,pos2+1))
   end
   if (valido?(pos1,pos2-1))
      neighbors.push(swapPosBoard(board,pos1,pos2,pos1,pos2-1))
   end
   return neighbors
end

board1=[[1,6,2,3],[5,10,7,4],[9,14,11,8],[13,0,15,12]]
##board1=[[2,0,3,4],[1,6,7,8],[5,9,10,11],[13,14,15,12]]

#board1=[[2,6,8,3],[1,14,9,11],[7,12,13,0],[5,15,4,10]]
goal=[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,0]]

res = Astar(board1,goal,method(:distanceBetween),
      method(:heuristicCostEstimate),
      method(:neighborNodes))

res.reverse.each do |item|
    printBoard item
end

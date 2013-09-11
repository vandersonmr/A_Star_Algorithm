# Algorithm A*
# Devlopers: Vanderson M. Rosario <vandersonmr2@gmail.com>
# 	     Diogo T. Murata <diogomurata@gmail.com>
# This code is under MIT licence.
#
# board[4][4] being 1 a position ocupated and 0 for blank.
#	0 - blank
#	1 - Ocupated

def getLower(openSet,f_score)
    lowest = openSet.first
    lowestValue = f_score[lowest]
    openSet.each do |item|
        if(f_score[item] < lowestValue)
            lowest = item
            lowestValue = f_score[item]
        end
    end
    return lowest
end

def reconstruct_path(came_from, current_node,path)
    next_node = current_node
    while(came_from.include?(next_node))
        path.push(next_node)
        next_node = came_from[next_node]
    end
end

def Astar(start,goal,distance_between,
          heuristic_cost_estimate,neighbor_nodes)

    closedSet=[]
    openSet=[start]
    came_from={}
    g_score = {}
    f_score = {}

    g_score[start]=0
    f_score[start]=g_score[start]
    + heuristic_cost_estimate.call(start,goal)

    while (not openSet.empty?)

        current=getLower(openSet,f_score)
        if(current == goal)
            path = []
            reconstruct_path(came_from, goal,path)
            return path
        end

        openSet.delete current
        closedSet.push current

        neighborhood=neighbor_nodes.call(current)

        neighborhood.each do |neighbor|

            tentative_g_score = g_score[current] + distance_between.call(neighbor,current)

            if (closedSet.include?(neighbor))
                if(tentative_g_score >= g_score[neighbor])
                    next
                end
            end

            if (!closedSet.include?(neighbor) || tentative_g_score < g_score[neighbor])
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g_score
                f_score[neighbor] = g_score[neighbor] + heuristic_cost_estimate.call(neighbor,goal)

                if (!openSet.include?(neighbor))
                    openSet.push(neighbor)
                end
            end
        end
    end
    return false;
end


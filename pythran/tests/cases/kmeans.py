#pythran export test()
#norunas test() because of random input
#bench test()
import  math, random

# a point is a tuple
# a cluster is a list of tuple and a point (the centroid)

def calculateCentroid(cluster):
    reduce_coord = lambda i: reduce(lambda x,p : x + p[i], cluster,0.0)
    centroid_coords = [reduce_coord(i)/len(cluster) for i in range(len(cluster[0]))]
    return centroid_coords

def kmeans(points, k, cutoff):
    initial = random.sample(points, k)
    clusters = [[p] for p in initial]
    centroids = [ calculateCentroid(c) for c in clusters ]
    while True:
        lists = [ [] for c in clusters]
        for p in points:
            smallest_distance = getDistance(p,centroids[0])
            index = 0
            for i in range(len(clusters[1:])):
                distance = getDistance(p, centroids[i+1])
                if distance < smallest_distance:
                    smallest_distance = distance
                    index = i+1
            lists[index].append(p)
        biggest_shift = 0.0
        for i in range(len(clusters)):
            if lists[i]:
                new_cluster, new_centroid = (lists[i], calculateCentroid(lists[i]))
                shift = getDistance(centroids[i], new_centroid)
                clusters[i] = new_cluster
                centroids[i] = new_centroid
                biggest_shift = max(biggest_shift, shift)
        if biggest_shift < cutoff:
            break
    return clusters

def getDistance(a, b):
    ret = reduce(lambda x,y: x + pow((a[y]-b[y]), 2),range(len(a)),0.0)
    return math.sqrt(ret)

def makeRandomPoint(n, lower, upper):
    return [random.uniform(lower, upper) for i in range(n)]

def test():
    num_points, dim, k, cutoff, lower, upper = 500, 10, 50, 0.001, 0, 2000
    points = [ makeRandomPoint(dim, lower, upper) for i in range(num_points) ]
    clusters = kmeans(points, k, cutoff)
    #for c in clusters:
    #    print c
    return clusters

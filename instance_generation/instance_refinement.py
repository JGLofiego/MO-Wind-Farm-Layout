import matplotlib.pyplot as plt
import shapely
import random

colors = ["red", "green", "blue"]

def gen_hole(polygon: shapely.Polygon):
    new_hole = []
    hole_max = min(1000, (polygon.area ** 0.5) * 0.3)
    
    for i in range(random.randint(3, 7)):
        new_hole.append(tuple([random.uniform(0.0, hole_max), random.uniform(0.0, hole_max)]))
    
    new_hole = shapely.Polygon(new_hole)
    
    new_hole = shapely.Polygon(new_hole.convex_hull)
    
    minx, miny, maxx, maxy = polygon.bounds

    point = shapely.Point(0, 0)
    
    while(not polygon.contains(point)):
        point = shapely.Point([random.uniform(minx, maxx), random.uniform(miny, maxy)])
    
    distance = point - new_hole.centroid
    
    coords = new_hole.exterior.coords[:]
    
    for i in range(len(coords)):
        coords[i] = (coords[i][0] + distance.x, coords[i][1] + distance.y)
    
    new_hole = shapely.Polygon(coords)
    
    return polygon.difference(new_hole)
    
def gen_holes(polygon: shapely.Polygon, qtty):

    for i in range(qtty):
        copy = polygon
        
        while(copy.equals(polygon)):
            copy = polygon
            copy = gen_hole(copy)
            
        while(copy.geom_type == "MultiPolygon" or copy.equals(polygon)):
            copy = polygon
            copy = gen_hole(copy)
        
        polygon = copy
    
    return polygon

def gen_structure(polygon: shapely.Polygon):
    minx, miny, maxx, maxy = polygon.bounds
    
    pointIn = shapely.Point([random.uniform(100000.0, 150000.0), random.uniform(100000.0, 150000.0)])
    
    while(not polygon.contains(pointIn)):
        pointIn = shapely.Point([random.uniform(minx, maxx), random.uniform(miny, maxy)])
        
    pointOut = shapely.Point([random.uniform(100000.0, 150000.0), random.uniform(100000.0, 150000.0)])
    
    while(polygon.contains(pointOut)):
        pointOut = shapely.Point([random.uniform(minx, maxx), random.uniform(miny, maxy)])
        
    
    dist = random.uniform(polygon.length / 300, polygon.length / 100)
    
    paceX = pointOut.x - pointIn.x
    paceY = pointOut.y - pointIn.y
    
    line = shapely.LineString([pointIn, pointOut])
    
    left = [shapely.Point(c) for c in line.parallel_offset(dist/2, "left").coords]
    right = [shapely.Point(p) for p in line.parallel_offset(dist/2, "right").coords]
    
    structure = shapely.Polygon(left + right).convex_hull
            
    return polygon.difference(structure)

def gen_structures(polygon: shapely.Polygon, qtty):
    for i in range(qtty):
        copy = polygon
        
        copy = gen_structure(copy)
            
        while(copy.geom_type == "MultiPolygon"):
            copy = polygon
            copy = gen_structure(copy)
        
        polygon = copy
    
    return polygon
    


polygons = []
points = []

path = "out.txt"

f = open(path, 'r')

for line in f.readlines():
    if len(line.split()) == 2:
        x, y = map(float, line.split())
        points.append(tuple([x, y]))
    if len(line.split()) == 0:
        polygons.append(shapely.Polygon(points))
        points.clear()
    

for i in range(len(polygons)):
    num_structs = random.randint(1, 4)
    num_holes = random.randint(2, 5)
    polygons[i] = gen_holes(polygons[i], num_holes)
    polygons[i] = gen_structures(polygons[i], num_structs)
    xe, ye = polygons[i].exterior.xy
    for inner in polygons[i].interiors:
        xi, yi = zip(*inner.coords[:])
        plt.plot(xi, yi, color=colors[i])
    plt.plot(xe, ye, color=colors[i])

plt.show()
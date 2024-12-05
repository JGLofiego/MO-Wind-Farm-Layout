import shapely, random
import matplotlib.pyplot as plt
import math

def polygon_order(point : tuple):
    return math.atan2(point[1], point[0])

def gen_polygon(num_vertex) -> shapely.Polygon:    
    points = []
    
    index_leastX = 0
    
    for i in range(num_vertex):
        x = random.uniform(100000.0, 150000.0)
        y = random.uniform(100000.0, 150000.0)
        
        points.append(tuple([x, y]))
        
        if points[index_leastX][0] > x:
            index_leastX = i
    
    points[0], points[index_leastX] = points[index_leastX], points[0]
    
    rest_points = points[1:]
    rest_points.sort(key=lambda x: math.atan2(x[1] - points[0][1], x[0] - points[0][0]))
    
    points = [points[0]] + rest_points
    
    polygon = shapely.Polygon(points)
    
    return polygon

def scale(polygon: shapely.Polygon, scale_factor: float):
    pointsX, pointsY = polygon.exterior.coords.xy
    
    pointsX = [x * scale_factor for x in pointsX]
    pointsY = [x * scale_factor for x in pointsY]
    
    resized_poly = shapely.Polygon([pointsX[i], pointsY[i]] for i in range(len(pointsX)))
    
    paceX = polygon.centroid.x - resized_poly.centroid.x
    paceY = polygon.centroid.y - resized_poly.centroid.y
    
    pointsX = [x + paceX for x in pointsX]
    pointsY = [x + paceY for x in pointsY]
    
    resized_poly = shapely.Polygon([pointsX[i], pointsY[i]] for i in range(len(pointsX)))
    
    return resized_poly
    

def gen_layout(num_zones) -> list[shapely.Polygon]:
    polygons : list[shapely.Polygon] = []
    area = 0
    
    i_l_area = 0
    i_h_area = 0

    for i in range(num_zones):
        polygons.append(gen_polygon(random.randint(3, 9)))
            
        area += polygons[i].area / (1000000)
    
    print(area)
    
    while area > 550:
        for i in range(num_zones):
            if polygons[i_h_area].area < polygons[i].area:
                i_h_area = i
        
        area -= polygons[i_h_area].area / 1000000
        
        polygons[i_h_area] = scale(polygons[i_h_area], 0.9)
        
        area += polygons[i_h_area].area / 1000000
    
    print(area)
                
            
    return polygons
        
polygons = gen_layout(random.randint(1, 3))

for i in range(len(polygons)):
    xe, ye = polygons[i].exterior.xy
    plt.plot(xe, ye)

plt.show()
        
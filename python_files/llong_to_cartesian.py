import math
earth_radius = 6371 # km

print( " input lat1 long1 lat2 long2 ")

lat1 = 51.283 * math.pi / 180
long1 = 30.233 * math.pi / 180

lat2 = 51.467 * math.pi / 180
long2 = 31.25 * math.pi / 180

x1 = earth_radius * math.sin(lat1) * math.cos(long1)
y1 = earth_radius * math.sin(lat1) * math.sin(long1)
z1 = earth_radius * math.cos(lat1)

x2 = earth_radius * math.sin(lat2) * math.cos(long2)
y2 = earth_radius * math.sin(lat2) * math.sin(long2)
z2 = earth_radius * math.cos(lat2)

print( math.dist( (x1,y1,z1), (x2,y2,z2) ) )

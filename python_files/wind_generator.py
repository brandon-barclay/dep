
import csv
import math
import sys
filename = sys.argv[-1]

wind_data_x = []
wind_data_y = []

with open(filename, newline='') as file:
    reader = csv.DictReader(file)
    for row in reader:
        speed = float(row['windspeed']) * 16.6667
        dir = float(row['winddir'])

        x = math.cos(dir + 180)
        y = math.sin(dir + 180)

        wind_data_x.append(x * speed)
        wind_data_y.append(y * speed)

with open("converted_" + filename,'w',newline='') as file:
    reader = csv.writer(file,delimiter=' ')
    reader.writerow(['Time', 'X_vel', 'Y_vel', 'Z_vel'])
    for i in range(len(wind_data_x)):
        reader.writerow([i*60, wind_data_x[i], wind_data_y[i], 0.0])

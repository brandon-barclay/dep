
import csv
import math

wind_data_x = []
wind_data_y = []

with open('wind_data.csv',newline='') as file:
    reader = csv.DictReader(file)
    for row in reader:
        speed = float(row['windspeed'])
        dir = float(row['winddir'])

        x = math.cos(dir + 180)
        y = math.sin(dir + 180)

        wind_data_x.append(x * speed)
        wind_data_y.append(y * speed)

with open('converted_wind_data.csv','w',newline='') as file:
    reader = csv.writer(file,delimiter=' ')
    reader.writerow(['Time', 'X_vel', 'Y_vel', 'Z_vel'])
    for i in range(len(wind_data_x)):
        reader.writerow([i*60, wind_data_x[i], wind_data_y[i], 0.0])

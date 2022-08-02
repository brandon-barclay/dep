
import csv
import math
import sys
filename = sys.argv[-1]

wind_data_x = []
wind_data_y = []
wind_data_time = []

with open(filename, newline='') as file:
    reader = csv.DictReader(file)
    i = 0
    for row in reader:
        if ( row['windspeed'] != '' and row['winddir'] != '') :
            speed = float(row['windspeed']) * 16.6667 # k/h to m/min
            dir = float(row['winddir'])

            x = math.sin(math.radians( dir + 180 ))
            y = math.cos(math.radians( dir + 180 ))


            wind_data_x.append(x * speed)
            wind_data_y.append(y * speed)
            wind_data_time.append(i * 60)
        i += 1

with open("converted_" + filename,'w',newline='') as file:
    reader = csv.writer(file,delimiter=' ')
    reader.writerow(['Time', 'X_vel', 'Y_vel', 'Z_vel'])
    for i in range(len(wind_data_x)):
        reader.writerow([wind_data_time[i], wind_data_x[i], wind_data_y[i], 0.0])

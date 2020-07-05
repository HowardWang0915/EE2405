# Part. 1
#=======================================
# Import module
#  csv -- fileIO operation
import csv
#=======================================

# Part. 2
#=======================================
# Read cwb weather data
cwb_filename = '107061112.csv'
data = []
header = []
with open(cwb_filename) as csvfile:
    mycsv = csv.DictReader(csvfile)
    header = mycsv.fieldnames
    for row in mycsv:
        data.append(row)
#=======================================

# Part. 3
# =======================================
# Analyze data depend on your group and store it to target_data like:
# Remove the data whose value of the TEMP (temperature) column is '-99.000' or '-999.000'.
# Find out the maximum of the TEMP value from C0A880, C0F9A0, C0G640, C0R190, C0X260.
# Output the ID of the station and the maximum of it in the lexicographical order.
# If you cannot find the maximum, please output 'None'.
list_data = {
    "C0A880": 0,
    "C0F9A0": 0,
    "C0G640": 0,
    "C0R190": 0,
    "C0X260": 0
}

target_data = []
for orddict in data:
    if (orddict['station_id'] in list_data):
        if (float(orddict['TEMP']) > float(list_data[orddict['station_id']])):
            list_data[orddict['station_id']] = float(orddict['TEMP'])
for station in list_data:
    if list_data[station] == 0:
        list_data[station] = 'NONE'
# [['C0A880', 27.0], ['C0F9A0', 22.0], ['C0G640', 28.0], ['C0R190', 'None'], ['C0X260', 27.0]]

for key in sorted(list_data.keys()):
    new_list = [key, list_data[key]]
    target_data.append(new_list)



# =======================================
# Part. 4
# =======================================
# Print result

print(target_data)
# ========================================

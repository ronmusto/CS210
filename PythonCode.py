import re
import string


def PrintList(): #Counts each occurance of every item in the list
    filename = "GroceryList.txt"
    file = open(filename, "r")
    data = file.readlines()
    file.close()
    data_count = {}
    for item in data:
        if item.strip() not in data_count:
            data_count[item.strip()] = 1
        else:
    	    data_count[item.strip()] += 1
    for item, count in data_count.items():
	    print(item, count)

def ItemCount(v): #Counts each occurance of a specified item in the list
    filename = "GroceryList.txt"
    file = open(filename, "r")
    data = file.readlines()
    file.close()
    data_count = {}
    for item in data:
        if item.strip() not in data_count:
            data_count[item.strip()] = 1
        else:
            data_count[item.strip()] += 1
    if v in data_count:
        return(data_count[v])
    else:
        print("Item was not bought today or does not exist...")
    return 0

def CreateFile(): #Creates file frequency.dat
    fileName = "GroceryList.txt"
    file = open(fileName, "r")
    data = file.readlines()
    file.close()
    data_count = {}
    for item in data:
        if item.strip() not in data_count:
            data_count[item.strip()] = 1
        else:
    	    data_count[item.strip()] += 1
    fileName = "frequency.dat"    
    file = open(fileName, "w")
    for item, count in data_count.items():
        itemFrequency = item + " " + str(count) + "\n"
        file.write(itemFrequency)
    file.close()
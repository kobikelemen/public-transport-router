


with open('bus_sequences/stop_name.txt', 'r') as file:
    filedata = file.readlines()


remove = [' [DLR]', ' >T<', ' <>', ' <> #', ' #', " >R<", ". >R<"]

for i in range(len(filedata)):
    for r in remove:
        if r in filedata[i]:
            filedata[i] = filedata[i].replace(r, '')
            filedata[i].strip()

with open('bus_sequences/stop_name_cleaned.txt', 'w') as file:
    for i in filedata:
        file.write(i)


# print(filedata)
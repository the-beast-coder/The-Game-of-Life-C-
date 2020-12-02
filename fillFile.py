boardFile = open("rsrc/board.txt", "w");
rows = int(input("How many rows / columns do you want?"))

textToAdd = "";

addingElements = True

for i in range(rows):
    for j in range(rows):
        textToAdd += "0"
    textToAdd += "\n"
boardFile.write(textToAdd);

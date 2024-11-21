import string
import random

mapIns = {}
mapDel = {}

fIns = open("cost_insert.txt", "w")
fDel = open("cost_delete.txt", "w")
fRep = open("cost_replace.txt", "w")
fTrans = open("cost_transpose.txt", "w")


for char in string.ascii_lowercase:
    mapIns[char] = random.randint(1, 2)
    fIns.write(str(mapIns.get(char)))
    if char != "z":
        fIns.write(" ")


for char in string.ascii_lowercase:
    mapDel[char] = random.randint(1, 2)
    fDel.write(str(mapDel.get(char)))
    if char != "z":
        fDel.write(" ")

for a in mapIns:
    for b in mapDel:
        if a == b:
            fRep.write("0")
        else:
            fRep.write(str(mapDel.get(a) + mapIns.get(b) - 1))
        if b != "z":
            fRep.write(" ")
    if a != "z":
        fRep.write("\n")

for a in mapIns:
    for b in mapDel:
        if a == b:
            fTrans.write("0")
        else:
            fTrans.write(
                str(
                    min(mapIns.get(a) + mapDel.get(a), mapIns.get(b) + mapDel.get(b))
                    - 1
                )
            )
        if b != "z":
            fTrans.write(" ")
    if a != "z":
        fTrans.write("\n")

fIns.close()
fDel.close()
fRep.close()
fTrans.close()

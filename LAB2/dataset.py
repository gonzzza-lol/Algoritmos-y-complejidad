import random
import string


def randomString(longitud):
    res = "".join(random.choices(string.ascii_lowercase, k=longitud))
    if not res:
        return "-"
    else:
        return res


def editString(s1, n):
    if s1 == "-":
        s1 = ""

    s2 = list(s1)
    op = random.choice(["ins", "del", "sub", "trans", "null"])

    for _ in range(n):
        if op == "ins":
            pos = random.randint(0, len(s2))
            char = random.choice(string.ascii_lowercase)
            s2.insert(pos, char)

        elif op == "del" and len(s2) > 0:
            pos = random.randint(0, len(s2) - 1)
            s2.pop(pos)

        elif op == "sub" and len(s2) > 0:
            pos = random.randint(0, len(s2) - 1)
            char = random.choice(string.ascii_lowercase)
            s2[pos] = char

        elif op == "trans" and len(s2) > 1:
            pos = random.randint(0, len(s2) - 2)
            s2[pos], s2[pos + 1] = (
                s2[pos + 1],
                s2[pos],
            )

        elif op == "null":
            continue

    res = "".join(s2)
    if not res:
        return "-"
    else:
        return res


def generador(n, nombre_archivo="datasets/dataset.txt"):
    with open(nombre_archivo, "w") as archivo:
        for _ in range(n):
            longitud = random.randint(0, 10)
            s1 = randomString(longitud)
            s2 = editString(s1, random.randint(0, 10))
            archivo.write(f"{s1} {s2}\n")


# En caso de quere cambiar el numero de pruebas a realizar,
# modificar el numero de la funcion de abajo
generador(50)

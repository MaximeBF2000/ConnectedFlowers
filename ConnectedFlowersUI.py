import requests
import json

url_api = "https://api.thinger.io/"
parametre = "oauth/token"

# body = "grant_type=password&username=Corantin&password=123456789"
# header = "Content-Type:application/x-www-form-urlencoded"
main_api = url_api + parametre

monjson = json.dumps([])

mydata = {
    "Content-Type": "application/x-www-form-urlencoded",
    "grant_type": "password",
    "username": "Corantin",
    "password": "123456789"
}

validtoken = requests.post(main_api, data= mydata).json()

#print(validtoken)

parametre ="v1/users/Corantin/devices?authorization="+ validtoken["access_token"]

main_api =url_api + parametre
object_api = requests.get(main_api, params = mydata)

#print(object_api.json())

devices = object_api.json()
verifDevice=1
while (verifDevice == 1):
    print ("Devices disponibles : ")
    print("")
    for device in devices:
        print(device["device"])
    print("\n")
    choice = input("Selectionner votre device : ")
    for device in devices:
        if choice == device["device"]:
            useDevice = device["device"]
            verifDevice=0
        else:
            print("Le device selectionne n'existe pas")

verifDevice=0
print (' ')
choosen_device = device["device"]
print ("vous avez selectionne : ", choosen_device)
# print(object_api.json())


parametre = "v2/users/Corantin/devices/" + choosen_device + "/light?authorization="+ validtoken["access_token"]
main_api = url_api + parametre
object_api = requests.get(main_api)
json_light = object_api.json()

print("Light : ",int(json_light["out"]), "lux")

parametre = "v2/users/Corantin/devices/" + choosen_device + "/temperature?authorization="+ validtoken["access_token"]
main_api = url_api + parametre
object_api = requests.get(main_api)
json_temp = object_api.json()

print("Temperature : ", json_temp["out"], "degres")

parametre = "v2/users/Corantin/devices/" + choosen_device + "/humidity?authorization="+ validtoken["access_token"]
main_api = url_api + parametre
object_api = requests.get(main_api)
json_humidity = object_api.json()

print("Humidity : ", json_humidity["out"], "%")

def readfile(filename):
    fichier = open(filename, "r")
    finaltab = []
    for line in fichier:
        smalltab = line.replace("\n", "").split(";")
        finaltab.append(smalltab)
    return finaltab



def treatPlant(plant):
    # print(plant[0], plant[2], plant[3], plant[4])
    # Light
    if int(plant[2]) > int(json_light["out"]):
        print("La luminosite est trop eleve pour cette plante")
    elif int(plant[2]) < int(json_light["out"]):
        print("La luminosite est trop faible pour cette plante")
    else:
        print("Excellente luminosite")
    # Temperature
    if int(plant[3]) > int(json_temp["out"]):
        print("La temperature est trop eleve pour cette plante")
    elif int(plant[3]) < int(json_temp["out"]):
        print("La temperature est trop faible pour cette plante")
    else:
        print("Excellente temperature")
    # Humidite
    if int(plant[4]) > int(json_humidity["out"]):
        print("La humidite est trop eleve pour cette plante")
    elif int(plant[4]) < int(json_humidity["out"]):
        print("La humidite est trop faible pour cette plante")
    else:
        print("Excellente temperature")


def plantlisting(fichier):
    mauvaisChoix = False
    plants = readfile(fichier) 
    for i in range (1, len(plants)):
        print(plants[i][0], end="  |  ")
    choix = input("Quelle plante voulez vous choisir ?")
    for i in range (1, len(plants)):
        if choix == plants[i][0]:
            treatPlant(plants[i])
        else :
            mauvaisChoix = True
    # if mauvaisChoix == True:
    #     print("La plante que vous avez entre n'est pas dans notre base de donnees")
        

plantlisting("bdd_plantes.csv")



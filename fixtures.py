import random

teams1=["Gongagonga","Zambarani","Black Eagles","Nurses","Clippers","Sigalagala","Veterans","Pirates","Snipers","Rangers","Rovers","Yanga"]
teams2=["Gongagonga","Zambarani","Black Eagles","Nurses","Clippers","Sigalagala","Veterans","Pirates","Snipers","Rangers","Rovers","Yanga"]

random.shuffle(teams1)
random.shuffle(teams2)
# print(teams1)
# print(teams2)
fixture=[]
num=10
for team1,team2 in zip(teams1,teams2):
    print(team1 + " vs " +team2)
    if team1==team2:
        print("Fixture Not genarated try again")
        break
    current_fixture=[team1,team2]
    fixture.append(current_fixture)
print(fixture)    
    
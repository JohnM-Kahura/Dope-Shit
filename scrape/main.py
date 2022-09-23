import csv
import requests
from bs4 import BeautifulSoup
def get_stats(link):
    html=requests.get(link).text

    soup=BeautifulSoup(html,'lxml')
    # get all the stats of a given house
    house_stats=soup.find("div",class_='stats row')

    capacity=house_stats.find_all("div")
    stats={}
    for i in capacity:
        stat=i.text.split('\n')

        x=stat[0].split(':')
        stats[x[0]]=x[1]
    print(stats)

    return stats
html=requests.get('https://web.saumag.edu/housing/options/').text
soup=BeautifulSoup(html,'lxml')
university_houses=soup.find_all("div",class_='dp-wrap')
stats=[]
house_names=[]
for house in university_houses:
    house_name=house.find('h3').text
    link_to_house=house.find('a').get('href')
    house_names.append(house_name)
    stats.append(get_stats(link_to_house))
fields = ['Capacity', 'Gender', 'Name' 'Flooring', 'Number of Floors','Mattress Size','Room_Types'] 
with open('houses.csv', 'w') as c: 
    writer = csv.writer(c) 
    writer.writerow(fields)         
    for i,stat  in enumerate(stats):
        if 'Room Types' in stat: 
            pass
        else:
            stat['Room Types']=' '
        row=[stat['Capacity'],stat['Gender'],house_names[i].strip(),stat['Flooring'],stat['Number of Floors'],stat['Mattress Size'],stat['Room Types']]    
      

        writer.writerow(row)


   



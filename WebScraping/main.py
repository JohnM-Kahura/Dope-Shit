import csv
import requests
from bs4 import BeautifulSoup


def get_stats(link): # this takes each link and get all the properties a house has
    html_text=requests.get(link).text

    soup=BeautifulSoup(html_text,'lxml')
    stats=soup.find("div",class_='stats row')

    capacity=stats.find_all("div")
    final_stats_obj={}
    for i in capacity:
        stat=i.text.split('\n')

        temp=stat[0].split(':')
        final_stats_obj[temp[0]]=temp[1]
    # print(len(final_stats_obj))

    return final_stats_obj
html_text=requests.get('https://web.saumag.edu/housing/options/').text
soup=BeautifulSoup(html_text,'lxml')

houses=soup.find_all("div",class_='dp-wrap')
final_objs=[]
house_names=[]
for house in houses:
    house_name=house.find('h3').text
    house_link=house.find('a').get('href')

    house_names.append(house_name)
    final_objs.append(get_stats(house_link))
print(final_objs[0])

fields = ['Name', 'Flooring', 'Capacity' 'Gender', 'Mattress_Size','Number_of_Floors','Room_Types'] 
with open('houses_scrape.csv', 'w') as csvfile: 
    # creating a csv writer object 
    csvwriter = csv.writer(csvfile) 
   
    # writing the fields 
    csvwriter.writerow(fields) 
        
    for i,final_obj  in enumerate(final_objs):
        if 'Room Types' in final_obj: #some houses do not contain Room types so you need to give a deafault empty string for the writing to csv to occur
            pass
        else:
            final_obj['Room Types']=' '
        row=[house_names[i].strip(),final_obj['Flooring'],final_obj['Capacity'],final_obj['Gender'],final_obj['Mattress Size'],final_obj['Number of Floors'],final_obj['Room Types']]    
        print(row) #print for debug

        csvwriter.writerow(row)


   



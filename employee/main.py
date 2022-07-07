import os
print("Welcome to the Employee Management System:\n")
choice=input("Type 1 to Enter new Employe and 2 to get employee information:")
if(choice=="1"):
    first_name=input("Employee First Name:")
    last_name=input("Employee Last Name:")
    employeeID=input("Employee ID:")
    field=input("Employee Work Field:")
    if(os.path.exists('employee_detail.txt')==True):
        with open("employee_detail.txt",'a') as f:
        
            f.write(first_name+","+last_name+","+employeeID+","+field+"\n")
            f.close()
    else:
        with open("employee_detail.txt",'w') as f:
        
            f.write(first_name+","+last_name+","+employeeID+","+field+"\n")
            f.close()
elif(choice=="2"):
     with open("employee_detail.txt",'r') as f:
        employee_data=f.read().split('\n')
        print(employee_data)
        f.close()

        
        
else:
    print("Please enter 1 or 2!!")



# Implement a new data type, called date, and implement operations
# date: 2022/09/22


months = ["January", "February", "March", "April", "May", "June",
          "July", "August", "September", "October", "November", "December"]

weeks = ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"]

days1 = [31,28,31,30,31,30,31,31,30,31,30,31]
days2 = [31,29,31,30,31,30,31,31,30,31,30,31]

class date:
    def __init__(self,date):
        b = date.split("/")
        self.y,self.m,self.d=int(b[0]),int(b[1]),int(b[2])

def IsLeapYear(y):
    return ((y%4==0 and y%100!=0) or (y%400)==0)

def GetNowDays(date):
    days=0
    m=date.m-1
    while m>0:
        days+=days2[m-1] if IsLeapYear(date.y) else days1[m-1]
        m-=1
    days+=date.d
    return(days)

def DayOfWeek(date1):
    date2=date('1582/10/18')
    w=DateSub(date1,date2)%7
    return(weeks[w])

def DateSub(date1, date2):
    days=0
    temp=date1.y-date2.y
    # days+=1 if temp>0 else 0
    while(temp>0):
        days+=366 if IsLeapYear(date2.y+temp-1) else 365
        temp-=1
    return(days+GetNowDays(date1)-GetNowDays(date2))

def DateAdd(date,n):
    y=date.y
    n+=GetNowDays(date)
    while n>365:
        if IsLeapYear(y):
            if n>366:
                n-=366
                y+=1
            else:
                break
        else:
            n-=365
            y+=1
    while n<=0:
        n+=366 if IsLeapYear(y-1) else 365
        y-=1 
    mm=0
    while n>0:
        if IsLeapYear(y):
            if n>days2[mm]:
                n-=days2[mm]
            else:
                break
        else:
            if n>days1[mm]:
                n-=days1[mm]
            else:
                break
        mm=(mm+1)%12
    return(y,mm+1,n)

def transform(input):
    try:
        if '+' in input:
            b = input.split("+")
            date1=date(b[0])
            n=int(b[1])
            y,m,d=DateAdd(date1,n)
            print(f'{n} days after {months[date1.m-1]} {date1.d}, {date1.y} is {months[m-1]} {d}, {y}')
        elif '-' in input:
            b = input.split("-")
            date1=date(b[0])
            date2=date(b[1])
            X=DateSub(date1,date2) if date1.y >= date2.y else (-1)*DateSub(date2,date1)
            print(f'{X} days from {months[date1.m-1]} {date1.d}, {date1.y} to {months[date2.m-1]} {date2.d}, {date2.y}')
        else:
            b=date(input)
            X=DayOfWeek(b)
            print(f'{months[b.m-1]} {b.d}, {b.y} is {X}')
    except:
        print('文法有誤，請重新輸入\n')

print('1.印出當日為星期幾(yyyy/mm/dd)\n\
2.計算相隔天數(yyyy/mm/dd - YYYY/MM/DD)\n\
3.計算指定天數後的日期(yyyy/mm/dd + x)')

while True:
    transform(input('> '))

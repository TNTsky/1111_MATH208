# Implement a new data type, called date, and implement operations
# date: 2022/09/22


months = ["January", "February", "March", "April", "May", "June",
          "July", "August", "September", "October", "November", "December"]
weeks = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"]
days1 = [31,28,31,30,31,30,31,31,30,31,30,31]
days2 = [31,29,31,30,31,30,31,31,30,31,30,31]

# 建立新數據類型date,並初始化其物件屬性值(年,月,日)
class date:
    def __init__(self,date):
        b = date.split("/")
        self.y,self.m,self.d=int(b[0]),int(b[1]),int(b[2])

# 定義函式:檢查日期是否正確
def check(date):
    b = date.split("/")
    if len(b)==3:
        if int(b[0])>=0:
            if IsLeapYear(int(b[0])):
                if int(b[1])in range(1, 13) and int(b[2]) in range(1,days2[int(b[1])-1]+1):
                    return True
            else:
                if int(b[1])in range(1, 13) and int(b[2])in range(1,days1[int(b[1])-1]+1):
                    return True
    return False

# 定義函式:判斷是否為閏年
def IsLeapYear(y):
    return ((y%4==0 and y%100!=0) or (y%400)==0)

# 定義函式:計算日期為當年第幾天
def GetNowDays(date):
    days=0
    m=date.m-1
    while m>0:
        days+=days2[m-1] if IsLeapYear(date.y) else days1[m-1]
        m-=1
    days+=date.d
    return(days)

# 定義函式:計算當天為星期幾並回傳名稱
def DayOfWeek(date1):
    date2=date('1582/10/17')
    w=DateSub(date1,date2)%7
    return(weeks[w])

# 定義函式:計算相隔天數並回傳數字
def DateSub(date1, date2):
    days=0
    temp=date1.y-date2.y
    while(temp>0):
        days+=366 if IsLeapYear(date2.y+temp-1) else 365
        temp-=1
    return(days+GetNowDays(date1)-GetNowDays(date2))


# 定義函式:計算指定天數後的日期並回傳
def DateAdd(date1,n):
    y=date1.y
    n+=GetNowDays(date1)
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
    X=date(f'{y}/{mm+1}/{n}')
    return(X)

# 定義函式:主要操作及判斷採用何種功能
def operation(input):
    try:
        for i in input:
            if '+' in input:
                a = input.replace('-', '+-')
                a = a.replace('++-', '+-').replace('+ +', '+')
                b = a.split("+")
                if b[0]:
                    pass
                else:
                    b=b[1:]
                n=0
                date1=date('2000/1/1')
                find = 0
                for i in b:
                    if check(i) and find==0:
                        date1=date(i)
                        find=1
                    else:
                        Alphabet=False
                        for j in i:
                            if (j>='a' and j<='z')or(j>='A' and j<='Z'):
                                Alphabet=True
                                break
                        n+='' if Alphabet else int(eval(i))
                if find==0:
                    print('格式有誤，請重新輸入')
                    return
                date2=DateAdd(date1,n)
                print(f'{n} days after {months[date1.m-1]} {date1.d}, {date1.y} is {months[date2.m-1]} {date2.d}, {date2.y}')
                return

            elif '-' in input:
                b = input.split("-")
                if len(b)==2:
                    try:
                        if check(b[0]) and check(b[1]):
                            date1=date(b[0])
                            date2=date(b[1])
                        X=DateSub(date1,date2) if date1.y >= date2.y else (-1)*DateSub(date2,date1)
                        print(f'{X} days from {months[date1.m-1]} {date1.d}, {date1.y} to {months[date2.m-1]} {date2.d}, {date2.y}')
                        return
                    except:
                        pass
                operation(input.replace('-', '+-'))
                return

        if check(input):
            b=date(input)
        else:
            print('日期錯誤')
            return
        X=DayOfWeek(b)
        print(f'{months[b.m-1]} {b.d}, {b.y} is {X}')
        return
    except:
        print('文法有誤，請重新輸入')

# 提示功能
print('1.印出當日為星期幾(yyyy/mm/dd)\n\
2.計算相隔天數(yyyy/mm/dd - YYYY/MM/DD)\n\
3.計算指定天數後的日期(yyyy/mm/dd + x)')

# 使用迴圈重複輸入操作
while True:
    operation(input('> '))

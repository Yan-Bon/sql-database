commands = [
    "SELECT", "RESELECT", "RESPONSE", "INSERT", "UPDATE", "PRINT", "DELETE"
]

sign_for_sel_resel = [
    "id=", "name=", "group=", "rating="
]

ids = [ 
     "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", 
    "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", 
    "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", 
    "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", 
    "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", 
    "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", 
    "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", 
    "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160", "161", 
    "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180", "181", 
    "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197", "198", "199", "200", "201", 
    "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", 
    "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", 
    "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255", "256", "257", "258", "259", "260", "261", 
    "262", "263", "264", "265", "266", "267", "268", "269", "270", "271", "272", "273", "274", "275", "276", "277", "278", "279", "280", "281", 
    "282", "283", "284", "285", "286", "287", "288", "289", "290", "291", "292", "293", "294", "295", "296", "297", "298", "299", "300", "301", 
    "302", "303", "304", "305", "306", "307", "308", "309", "310", "311", "312", "313", "314", "315", "316", "317", "318", "319", "320", "321", 
    "322", "323", "324", "325", "326", "327", "328", "329", "330", "331", "332", "333", "334", "335", "336", "337", "338", "339", "340", "341", 
    "342", "343", "344", "345", "346", "347", "348", "349", "350", "351", "352", "353", "354", "355", "356", "357", "358", "359", "360", "361", 
    "362", "363", "364", "365", "366", "367", "368", "369", "370", "371", "372", "373", "374", "375", "376", "377", "378", "379", "380", "381", 
    "382", "383", "384", "385", "386", "387", "388", "389", "390", "391", "392", "393", "394", "395", "396", "397", "398", "399", "400", "401", 
    "402", "403", "404", "405", "406", "407", "408", "409", "410", "411", "412", "413", "414", "415", "416", "417", "418", "419", "420", "421", 
    "422", "423", "424", "425", "426", "427", "428", "429", "430", "431", "432", "433", "434", "435", "436", "437", "438", "439", "440", "441", 
    "442", "443", "444", "445", "446", "447", "448", "449", "450", "451", "452", "453", "454", "455", "456", "457", "458", "459", "460", "461", 
    "462", "463", "464", "465", "466", "467", "468", "469", "470", "471", "472", "473", "474", "475", "476", "477", "478", "479", "480", "481", 
    "482", "483", "484", "485", "486", "487", "488", "489", "490", "491", "492", "493", "494", "495", "496", "497", "498", "499", "500", "*"
]

ratings = [
    "2.0", "2.1", "2.2", "2.3", "2.4", "2.5", "2.6", "2.7", "2.8", "2.9", "3.0", "3.1", "3.2", "3.3", "3.4", "3.5", "3.6", "3.7", "3.8", "3.9", 
    "4.0", "4.1", "4.2", "4.3", "4.4", "4.5", "4.6", "4.7", "4.8", "4.9", "5.0", "5.1", "5.2", "5.3", "5.4", "5.5", "5.6", "5.7", "5.8", "5.9", 
"6.0", "6.1", "6.2", "6.3", "6.4", "6.5", "6.6", "6.7", "6.8", "6.9", 
"7.0", "7.1", "7.2", "7.3", "7.4", "7.5", "7.6", "7.7", "7.8", "7.9", 
"8.0", "8.1", "8.2", "8.3", "8.4", "8.5", "8.6", "8.7", "8.8", "8.9", 
"9.0", "9.1", "9.2", "9.3", "9.4", "9.5", "9.6", "9.7", "9.8", "9.9", 
"10.0", "*"
]

male_firstnames = [
    "Aleksandr", "Dmitriy", "Maksim", "Sergey", "Andrey", "Aleksey", "Artyom", "Ilya", "Kirill", "Mikhail",
"Ivan", "Roman", "Vladimir", "Pavel", "Nikita", "Egor", "Artur", "Gleb", "Konstantin", "Stanislav",
"Anton", "Viktor", "Georgiy", "Daniil", "Evgeniy", "Zakhar", "Lev", "Matvey", "Oleg", "Pyotr",
"Semyon", "Timofey", "Fyodor", "Yuriy", "Yaroslav", "Boris", "Valentin", "Grigoriy", "Denis", "Yefim",
"Igor", "Leonid", "Nikolay", "Ruslan", "Svyatoslav", "Timur", "Filipp", "Eduard", "Yan", "Vasiliy",
"Gennadiy", "David", "Yelisey", "Ignat", "Klim", "Mark", "Nazar", "Oskar", "Prokhor", "Radislav",
"Savva", "Taras", "Ustin", "Khariton", "Erik", "Yakov", "Albert", "Valeriy", "Vyacheslav", "German",
"Demid", "Yemelyan", "Zhdan", "Zurab", "Ibragim", "Kamil", "Luka", "Marat", "Nestor", "Odisey",
"Platon", "Ramil", "Stefan", "Teodor", "Umar", "Foma", "Tsezar", "Shamil", "Emir", "Yulian",
"Yaromir", "Adam", "Bogdan", "Vlad", "Gavriil", "Damir", "Evdokim", "Zhorzh", "Zinoviy", "Ildar"
]

female_firstnames = [
    "Anna", "Elena", "Olga", "Natalya", "Irina", "Mariya", "Svetlana", "Tatyana", "Ekaterina", "Yuliya",
"Anastasiya", "Viktoriya", "Dariya", "Kseniya", "Alina", "Polina", "Valeriya", "Sofiya", "Aleksandra", "Veronika",
"Angelina", "Bogdana", "Vasilisa", "Galina", "Diana", "Evgeniya", "Zhanna", "Zlata", "Inna", "Kira",
"Larisa", "Margarita", "Nina", "Oksana", "Regina", "Snezhana", "Ulyana", "Fatima", "Elina", "Yana",
"Agata", "Bella", "Varvara", "Gulnara", "Darina", "Yeseniya", "Zoya", "Ivanna", "Karina", "Lyubov",
"Milana", "Nadezhda", "Olesya", "Raisa", "Serafima", "Tamara", "Ustinya", "Faina", "Tsvetana", "Sharlotta",
"Evelina", "Yuliana", "Yaroslava", "Alyona", "Berislava", "Valentina", "Gelena", "Dominika", "Yelizaveta", "Zhasmin",
"Zarina", "Izabella", "Kamilla", "Lyudmila", "Miroslava", "Nelli", "Oliviya", "Pelageya", "Rozalina", "Stanislava",
"Tereza", "Florentina", "Elvira", "Yunona", "Yasmina", "Adelina", "Bozhena", "Venera", "Gretta", "Debora",
"Evangelina", "Zhozefina", "Zemfira", "Iya", "Katarina", "Leyla", "Maya", "Naomi", "Ofeliya", "Roksana"
]

male_lastnames = [
    "Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov", "Vasilyev", "Popov", "Sokolov", "Mikhaylov", "Novikov",
"Fedorov", "Morozov", "Volkov", "Alekseyev", "Lebedev", "Semenov", "Egorov", "Pavlov", "Kozlov", "Stepanov",
"Nikolayev", "Orlov", "Romanov", "Solovyov", "Tikhonov", "Ushakov", "Filippov", "Kharitonov", "Tsvetkov", "Chernov",
"Shestakov", "Shcherbakov", "Yudin", "Yakovlev", "Baranov", "Belov", "Gromov", "Danilov", "Yefimov", "Zhukov",
"Zaytsev", "Isayev", "Karpov", "Lapin", "Maslov", "Nazarov", "Ovchinnikov", "Prokofyev", "Rybakov", "Savelyev",
"Tarasov", "Ustinov", "Fomin", "Khokhlov", "Cherkasov", "Shubin", "Shchukin", "Yashin", "Abramov", "Blinov",
"Vinogradov", "Galkin", "Dorofeyev", "Yeryomin", "Zhdanov", "Zuyev", "Ilyin", "Kalashnikov", "Loginov", "Melnikov",
"Nesterov", "Osipov", "Pakhomov", "Rogov", "Sazonov", "Trofimov", "Ulyanov", "Frolov", "Khabarov", "Tsarev",
"Chebotarev", "Shirokov", "Shcheglov", "Yakushev", "Andreyev", "Biryukov", "Vlasov", "Gorbunov", "Dementyev", "Yevseyev",
"Zhilin", "Zimin", "Knyazev", "Lytkin", "Mamontov", "Noskov", "Pankratov", "Rusakov", "Subbotin", "Tumanov"
]

female_lastnames = [name + "а" for name in male_lastnames]

male_patronymics = [
    "Aleksandrovich", "Dmitriyevich", "Sergeyevich", "Andreyevich", "Alekseyevich", "Artyomovich", "Ilyich", "Kirillovich",
"Vladimirovich", "Yevgenyevich", "Maksimovich", "Olegovich", "Romanovich", "Vitalyevich", "Gennadyevich",
"Anatolyevich", "Borisovich", "Valentinovich", "Georgiyevich", "Danilovich", "Yegorovich", "Zakharovich", "Igorevich",
"Leonidovich", "Mikhaylovich", "Nikolayevich", "Pavlovich", "Robertovich", "Stanislavovich", "Timofeyevich",
"Fyodorovich", "Yuryevich", "Yaroslavovich", "Arkadyevich", "Bogdanovich", "Valeryevich", "Gennadiyevich", "Denisovich",
"Yefimovich", "Ivanovich", "Konstantinovich", "Lvovich", "Matveyevich", "Nazarovich", "Olegovich", "Petrovich",
"Ruslanovich", "Semyonovich", "Tarasovich", "Umarovich", "Filippovich", "Kharitonovich", "Tsezarevich", "Shamilevich",
"Eduardovich", "Yukhymovich", "Yakovlevich", "Albertovich", "Vasilyevich", "Vyacheslavovich", "Germanovich", "Demidovich",
"Yevgrafovich", "Zhoresovich", "Zurabovich", "Ibragimovich", "Kamilevich", "Lukyanovich", "Maratovich", "Nestorovich",
"Odiseyevich", "Platonovich", "Ramirovich", "Stepanovich", "Teodorovich", "Umalatovich", "Fomich", "Khabibovich",
"Eldarovich", "Yuryevich", "Yanovich", "Arturovich", "Bronislavovich", "Vladislavovich", "Glebovich", "Demidovich"
]

female_patronymics = [
   "Aleksandrovna", "Dmitriyevna", "Sergeyevna", "Andreyevna", "Alekseyevna", "Artyomovna", "Ilyinichna", "Kirillovna",
"Vladimirovna", "Yevgenyevna", "Maksimovna", "Olegovna", "Romanovna", "Vitalyevna", "Gennadyevna",
"Anatolyevna", "Borisovna", "Valentinovna", "Georgiyevna", "Danilovna", "Yegorovna", "Zaharovna", "Igorevna",
"Leonidovna", "Mikhaylovna", "Nikolayevna", "Pavlovna", "Robertovna", "Stanislavovna", "Timofeyevna",
"Fyodorovna", "Yuryevna", "Yaroslavovna", "Arkadyevna", "Bogdanovna", "Valeryevna", "Gennadiyevna", "Denisovna",
"Yefimovna", "Ivanovna", "Konstantinovna", "Lvovna", "Matveyevna", "Nazarovna", "Olegovna", "Petrovna",
"Ruslanovna", "Semyonovna", "Tarasovna", "Umarovna", "Filippovna", "Kharitonovna", "Tsezarevna", "Shamilevna",
"Eduardovna", "Yukhimovna", "Yakovlevna", "Albertovna", "Vasilyevna", "Vyacheslavovna", "Germanovna", "Demidovna",
"Yevgrafovna", "Zhoresovna", "Zurabovna", "Ibragimovna", "Kamilevna", "Lukyanovna", "Maratovna", "Nestorovna",
"Odiseyevna", "Platonovna", "Ramirovna", "Stepanovna", "Teodorovna", "Umalatovna", "Fominichna", "Khabibovna",
"Eldarovna", "Yuryevna", "Yanovna", "Arturovna", "Bronislavovna", "Vladislavovna", "Glebovna", "Demidovna"
]

namess = male_firstnames + female_firstnames + male_lastnames + female_lastnames + male_patronymics + female_patronymics

additional_info = [
   "State-funded education", "Contract-based education", "Corporate-sponsored education",
"International student (contract)", "Athletic scholarship", "Student council activist",
"Enhanced academic scholarship", "Privileged category", "Science competition participant",
"Olympiad winner", "Transfer from another faculty", "Reinstated after dismissal",
"Repeating a year", "Individual study plan", "International programs participant",
"Internship abroad", "Military service deferment", "Combining work and study",
"Single parent", "Disability group 3", "Orphan", "From large family",
"Performing arts member", "Volunteer work", "Language courses",
"Major change", "Academic leave due to illness", "Debate club participant",
"Trade union member", "Rector's grant recipient", "Startup project participant",
"University employee", "Part-time education", "Evening classes",
"Distance learning", "Dual major", "Honors student",
"Archaeological expedition participant", "Scientific society member", "Journal publications",
"Theater studio member", "IT club member", "Hackathon winner",
"Erasmus+ participant", "Potanin Foundation scholar", "Chess team member",
"KVN team captain", "Student newspaper editor", "Photojournalist",
"Faculty chat administrator", "Freshmen mentor", "Event organizer",
"Choir member", "Literary club member", "Study blog author",
"Mobile app developer", "Case championship participant", "Corporate intern",
"Science Slam winner", "Model UN participant", "Environmental movement member",
"Sports league member", "Math tutor", "Programming consultant",
"Quest organizer", "Psychology club member", "Historical society member",
"Scientific papers author", "University website developer", "Conference moderator",
"AI projects participant", "Entrepreneurship club member", "Essay contest winner",
"Legal clinic volunteer", "Orphanage volunteer", "Film club member",
"Festival organizer", "Robotics competition participant", "Philosophy circle member",
"Podcast creator", "Game developer", "Biohacking participant",
"Tourism club member", "Design competition winner", "Media projects participant",
"Astronomy club member", "Charity events organizer", "Political debates participant",
"Logistics club member", "Custom term paper writer", "Chatbot developer",
"Neuroscience research participant", "Data science community member", "Startup competition winner",
"Architectural projects participant"
]

import random
from random import randint, uniform
from itertools import islice

def generate_fio(gender):
    if gender == "male":
        firstname = random.choice(male_firstnames)
        lastname = random.choice(male_lastnames)
    else:
        firstname = random.choice(female_firstnames)
        lastname = random.choice(female_lastnames)
    # В вашей базе используется только имя (name[64]), без фамилии и отчества
    return firstname

def generate_student():
    gender = random.choice(["male", "female"])
    name = generate_fio(gender)
    group = randint(100, 999)  # Группы в вашей системе обычно 3-значные
    rating = round(uniform(2.0, 10.0), 1)  # Рейтинг от 2.0 до 10.0
    info = random.choice(additional_info)
    return f"{name} {group} {rating} {info}"

def generate_criteria():
    """Генерация критериев для SELECT/RESELECT"""
    criteria = []
    # С вероятностью 50% добавляем критерий по имени
    if random.random() < 0.5:
        name = random.choice(male_firstnames + female_firstnames)
        if random.random() < 0.3:  # 30% chance for wildcard
            name = name[:random.randint(3, len(name))] + "*"
        criteria.append(f"name={name}")
    
    # С вероятностью 50% добавляем критерий по группе
    if random.random() < 0.5:
        group = randint(100, 999)
        if random.random() < 0.2:  # 20% chance for range
            group_end = min(999, group + randint(1, 10))
            criteria.append(f"group={group}-{group_end}")
        else:
            criteria.append(f"group={group}")
    
    # С вероятностью 50% добавляем критерий по рейтингу
    if random.random() < 0.5:
        min_rating = round(uniform(2.0, 8.0), 1)
        max_rating = round(min_rating + uniform(1.0, 2.0), 1)
        criteria.append(f"rating={min_rating}-{max_rating}")
    
    return " ".join(criteria)

def generate_command():
    command = random.choice(commands)
    
    if command in ["SELECT", "RESELECT"]:
        return f"{command} {generate_criteria()} END"
    
    elif command == "INSERT":
        return f"{command} {generate_student()} END"
    
    elif command == "UPDATE":
        # Генерируем критерии для выбора записей
        criteria = generate_criteria()
        # Генерируем новые значения
        updates = []
        if random.random() < 0.7:
            updates.append(f"name={generate_fio(random.choice(['male', 'female']))}")
        if random.random() < 0.7:
            updates.append(f"group={randint(100, 999)}")
        if random.random() < 0.7:
            updates.append(f"rating={round(uniform(2.0, 10.0), 1)}")
        if random.random() < 0.7:
            updates.append(f"info={random.choice(additional_info)}")
        
        return f"{command} {criteria} SET {' '.join(updates)} END"
    
    elif command == "DELETE":
        return f"{command} {generate_criteria()} END"
    
    elif command == "PRINT":
        fields = []
        if random.random() < 0.8:
            fields.append("name")
        if random.random() < 0.8:
            fields.append("group")
        if random.random() < 0.8:
            fields.append("rating")
        if random.random() < 0.5:
            fields.append("info")
        return f"{command} {' '.join(fields)} END"
    
    elif command == "RESPONSE":
        fields = []
        if random.random() < 0.8:
            fields.append("name")
        if random.random() < 0.8:
            fields.append("group")
        if random.random() < 0.8:
            fields.append("rating")
        if random.random() < 0.5:
            fields.append("info")
        return f"{command} {' '.join(fields)} END"

# Генерация 1000 команд
with open("commands.txt", "w", encoding="utf-8") as f:
    for _ in range(1000):
        cmd = generate_command()
        f.write(cmd + "\n")

create table champ(
    champion_name varchar(15),
    champion_id int default 0,
    primary key (champion_id)
);

load data local infile './champ.csv'
into table champ
fields terminated by ','
enclosed by '"'
lines terminated by '\n'
ignore 1 lines;




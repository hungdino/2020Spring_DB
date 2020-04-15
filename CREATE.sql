create table champ(
    champion_name varchar(15) NOT NULL,
    champion_id int default 0 NOT NULL,
    primary key (champion_id)
);

create table match_info(
    match_id int default 0 NOT NULL,
    duration int default 0 ,
    version varchar(15),
    primary key (match_id)
);




load data local infile './champs.csv'
into table champ
fields terminated by ','
enclosed by '"'
lines terminated by '\n'
ignore 1 lines;




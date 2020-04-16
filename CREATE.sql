CREATE TABLE champ(
    champion_name varchar(15) NOT NULL,
    champion_id int default 0 NOT NULL,
    PRIMARY KEY (champion_id)
);

CREATE TABLE match_info(
    match_id int default 0 NOT NULL,
    duration int default 0 ,
    version varchar(15),
    PRIMARY KEY (match_id)
);

CREATE TABLE participant(
    player_id int default 0 NOT NULL,
    match_id int default 0 NOT NULL,
    player tinyint default 0,
    champion_id int default 0 NOT NULL,
    ss1 varchar(15),
    ss2 varchar(15),
    position varchar(13) NOT NULL,
    PRIMARY KEY (player_id),
    FOREIGN KEY (match_id) REFERENCES match_info(match_id)
 );




load data local infile './champs.csv'
into table champ
fields terminated by ','
enclosed by '"'
lines terminated by '\r\n'
ignore 1 lines;




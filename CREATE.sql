CREATE TABLE champ(
    champion_name varchar(15) NOT NULL,
    champion_id int default 0 NOT NULL,
    PRIMARY KEY (champion_id)
);

load data local infile './champs.csv'
into table champ
fields terminated by ','
enclosed by '"'
lines terminated by '\n'
ignore 1 lines;

CREATE TABLE match_info(
    match_id int default 0 NOT NULL,
    duration int default 0 ,
    version varchar(15),
    PRIMARY KEY (match_id)
);

load data local infile './matches.csv'
into table match_info
fields terminated by ','
enclosed by '"'
lines terminated by '\r\n'
ignore 1 lines;

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

load data local infile './participants.csv'
into table participant
fields terminated by ','
enclosed by '"'
lines terminated by '\r\n'
ignore 1 lines;

CREATE TABLE teamban(
    match_id int default 0 NOT NULL,
    team char(1)  NOT NULL,
    champion_id int default 0 NOT NULL,
    banturn tinyint default 0 NOT NULL,
    PRIMARY KEY (match_id,banturn),
 );

load data local infile 'teambans.csv'
into table teamban
fields terminated by ','
enclosed by '"'
lines terminated by '\r\n'
ignore 1 lines;

CREATE TABLE stat(
    player_id int default 0 NOT NULL,
    win boolean default 0,
	item1 smallint,
	item2 smallint,
	item3 smallint,
	item4 smallint,
	item5 smallint,
	item6 smallint,
	kills tinyint default 0,
	deaths tinyint default 0,
	assists tinyint default 0,
	longesttimespentliving smallint default 0,
	doublekills tinyint default 0,
	triplekills tinyint default 0,
	quadrakills tinyint default 0,
	pentakills tinyint default 0,
	legendarykills tinyint default 0,
	goldearned mediumint default 0,
	firstblood boolean,
    PRIMARY KEY (player_id)
 );

load data local infile 'stats.csv'
into table stat
fields terminated by ','
enclosed by '"'
lines terminated by '\r\n'
ignore 1 lines;



SELECT champion_id
FROM participant
WHERE position = "JUNGLE";




SELECT DISTINCT position
FROM participant;
+-------------+
| position    |
+-------------+
| JUNGLE      |
| DUO_SUPPORT |
| DUO_CARRY   |
| TOP         |
| MID         |
| DUO         |
| SOLO        |
| NONE        |
+-------------+

DESCRIBE participant;                                  +-------------+-------------+------+-----+---------+-------+
| Field       | Type        | Null | Key | Default | Extra |
+-------------+-------------+------+-----+---------+-------+
| player_id   | int(11)     | NO   | PRI | 0       |       |
| match_id    | int(11)     | NO   | MUL | 0       |       |
| player      | tinyint(4)  | YES  |     | 0       |       |
| champion_id | int(11)     | NO   |     | 0       |       |
| ss1         | varchar(15) | YES  |     | NULL    |       |
| ss2         | varchar(15) | YES  |     | NULL    |       |
| position    | varchar(13) | NO   |     | NULL    |       |
+-------------+-------------+------+-----+---------+-------+
7 rows in set (0.00 sec)
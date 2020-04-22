
SELECT champion_name FROM champ
WHERE champion_id NOT IN
(
SELECT DISTINCT champion_id
FROM teamban 
NATURAL JOIN match_info
WHERE SUBSTRING_INDEX(version, ".", 2) = "7.7"
)
ORDER BY champion_name;
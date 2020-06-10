-- 在LOL中，有時會刻意選擇前/後期英雄確保遊戲時間進行到前/後面能有很大的勝率。列出當比賽遊戲時間在40~50分鐘 (duration) (皆包含邊界時間) 時五個位置 (TOP/MID/JUNGLE/DUO_CARRY/DUO_SUPPORT) 分別出現最多次的英雄（提示：between）

select final.position, champ.champion_name
from
(
    select list.position, list.champion_id
    from
    (
        select position, champion_id, count(champion_id) as cnt
        from
        (
            select match_id
            from match_info
            where duration >= 2400 and duration <= 3000
        ) as dur_match, 
        (
            select match_id, champion_id, position
            from participant
            where position = 'TOP' or position = 'MID' or position = 'JUNGLE'
            or position = 'DUO_CARRY' or position = 'DUO_SUPPORT'
        ) as par
        where par.match_id = dur_match.match_id
        group by position, champion_id
        order by cnt desc
    ) as list,
    (
        select grp_pos_champ.position, max(grp_pos_champ.cnt) as cnt
        from
        (
            select position, champion_id, count(champion_id) as cnt
            from
            (
                select match_id
                from match_info
                where duration >= 2400 and duration <= 3000
            ) as dur_match, 
            (
                select match_id, champion_id, position
                from participant
                where position = 'TOP' or position = 'MID' or position = 'JUNGLE'
                or position = 'DUO_CARRY' or position = 'DUO_SUPPORT'
            ) as par
            where par.match_id = dur_match.match_id
            group by position, champion_id
            order by cnt desc
        ) as grp_pos_champ
        group by grp_pos_champ.position
    ) as tmp
    where list.position = tmp.position
    and list.cnt = tmp.cnt
) as final, champ
where final.champion_id = champ.champion_id
order by final.position;
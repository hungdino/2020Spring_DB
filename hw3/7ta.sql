-- 列出五個位置 (TOP/MID/JUNGLE/DUO_CARRY/DUO_SUPPORT) 中，且總擊殺參與率 (總KDA = (總Kill + 總Assist) / 總Death) 最高的英雄與對應的總KDA值（提示：group by, sum）
 
select grp.position, grp.champion_name, tmp.kda
from
(
    select par_champ.position, par_champ.champion_name, 
        (sum(sub_stat.kills)+sum(sub_stat.assists))/sum(sub_stat.deaths) as sum_kda
    from 
    (
        select par.player_id, champ.champion_name, par.position
        from participant as par, champ
        where champ.champion_id = par.champion_id and
        (   par.position = 'TOP' or par.position = 'MID' or par.position = 'JUNGLE'
            or par.position = 'DUO_CARRY' or par.position = 'DUO_SUPPORT'
        )
    ) as par_champ,
    (
        select player_id, kills, deaths, assists
        from stat
    ) as sub_stat
    where par_champ.player_id = sub_stat.player_id
    group by par_champ.position, par_champ.champion_name
) as grp,
(
    select final.position, max(final.sum_kda) as kda
    from
    (
        select *
        from
        (
            select par_champ.position, par_champ.champion_name, 
                (sum(sub_stat.kills)+sum(sub_stat.assists))/sum(sub_stat.deaths) as sum_kda
            from 
            (
                select par.player_id, champ.champion_name, par.position
                from participant as par, champ
                where champ.champion_id = par.champion_id and
                (   par.position = 'TOP' or par.position = 'MID' or par.position = 'JUNGLE'
                    or par.position = 'DUO_CARRY' or par.position = 'DUO_SUPPORT'
                )
            ) as par_champ,
            (
                select player_id, kills, deaths, assists
                from stat
            ) as sub_stat
            where par_champ.player_id = sub_stat.player_id
            group by par_champ.position, par_champ.champion_name
        ) as grp
        order by grp.sum_kda desc
    ) as final
    group by final.position
) as tmp
where tmp.kda = grp.sum_kda
and tmp.position = grp.position
order by grp.position;
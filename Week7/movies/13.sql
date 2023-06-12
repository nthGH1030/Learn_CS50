select distinct name from people
join stars on stars.person_id = people.id
join movies on movies.id = stars.movie_id
where movies.id in
(
select movies.id from movies
join stars on stars.movie_id = movies.id
join people on people.id = stars.person_id
where people.name like "Kevin Bacon" and people.birth = 1958
)
and people.name != "Kevin Bacon"
;

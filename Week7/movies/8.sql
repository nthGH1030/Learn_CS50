select name from people
join stars on stars.person_id = people.id
join movies on movies.id = stars.movie_id
where movies.title = "Toy Story"
;
select AVG(rating) from movies
join ratings on ratings.movie_id = movies.id
where year = 2012
;

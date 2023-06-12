select title , rating
from movies
Join ratings on ratings.movie_id = movies.id
where year = 2010
order by rating desc, title asc
;
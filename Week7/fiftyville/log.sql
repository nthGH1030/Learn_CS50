-- Keep a log of any SQL queries you execute as you solve the mystery.

--The name of the thief
select name from people
where phone_number in
(select caller
from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60)
and
name in
(select name from people where license_plate in
(select license_plate
from bakery_security_logs
where year = 2021 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25))
and
name in
(select name from people
join bank_accounts on bank_accounts.person_id = people.id
where people.id in
(select person_id from bank_accounts
where account_number in
(select account_number from atm_transactions
where year = 2021 and month = 7 and day = 28 and atm_location like "leggett street")))
and
name in
(select name from people
where passport_number in
(select passport_number from passengers
join flights on flights.id = passengers.flight_id
where flights.id in
(select id from flights
where origin_airport_id in
(select id from airports
where city = 'Fiftyville')
and
id in
(select id from flights
where year = 2021 and month = 7 and day = 29 and hour = 8))))
;

-- The city the thief escape to
select city from airports where
id in
(select destination_airport_id from flights
where id in
(select id from flights
where origin_airport_id in
(select id from airports
where city = 'Fiftyville')
and
id in
(select id from flights
where year = 2021 and month = 7 and day = 29 and hour = 8)));

--The accompliance
select name from people where
phone_number =
(select receiver from phone_calls
where caller =
(select phone_number from people
where name = 'Bruce')
and year = 2021 and month = 7 and day = 28 and duration < 60);
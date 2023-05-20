# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file into a list of dictionary
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for team in reader:
            team['rating'] = int(team['rating'])
            teams.append(team)
        #print(teams)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # expected dictionry content = counts{'team': Uruguay, 'wins': '132'}
    i = 0
    while(i < N):
        winner = simulate_tournament(teams)
        if winner not in counts:
            counts[winner] = 1
        else:
            counts[winner] += 1
        i += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        # if team 1 wins
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        # if team 2 wins
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO

    # call simulate_round until theres only 1 winner
    winner = []
    winner = simulate_round(teams)
    while(len(winner) > 1):
        winner = simulate_round(winner)
    #print(winner[0]['team'])
    return winner[0]['team']


if __name__ == "__main__":
    main()

# LinkedListMovies

## Purpose
This project involves using linked lists to store data in a specified order. You will create a linked list that can be searched in multiple ways.

## Problem
SMAX, a spinoff of HBO MAX, has hired you to develop a database that stores movies and their ratings. Users can search for a movie to see its IMDb rating and Rotten Tomatoes score or search for top-scoring movies using various metrics.

## Input
The program should prompt for the name of a file containing the movie database. The data will be in the form of a space-delimited CSV file with the following format:

- Year is an integer
- Audience score is a float (viewers/10)
- Rotten Tomatoes score is a float (percentage)
- Movie name can be multiple words

## Menu
The program should display the following menu:
- **m**: Search by (m)ovie name
- **a**: List top 15 movies by (a)udience score
- **r**: List top 15 movies by (R)otten Tomatoes score
- **w**: Display (w)orst movie by Rotten Tomatoes score
- **i**: (I)nsert a new movie into the database
- **u**: (U)pdate a movie
- **q**: (Q)uit

### Menu Actions
- **m**: Prompt for the movie name and display its details.
- **i**: Prompt for all required items to add a new movie to the database, inserting it in the correct order for both scores.
- **u**: Prompt for a movie name, display its current data, and prompt for updated data. The updated movie should be deleted and re-inserted to maintain proper ordering.

## Output
The output should depend on the user's choice. Movies should be displayed with rank, name, year, audience score, and Rotten Tomatoes score. Numeric values should be right-justified, audience scores should have 1 decimal place, and Rotten Tomatoes scores should be rounded to the nearest whole percentage.

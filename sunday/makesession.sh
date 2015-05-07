#!/bin/bash

###########################################
# Update these lines to configure session
###########################################
starttime="2015-05-10 11:30 CEST"
length="4:00:00"
name="KTH Boot Camp 2015"

judges="polacek vinyals oswa nikbac sannemo" # any number of people, Kattis usernames
owner="vinyals"  # one person, Kattis username

# All problems in the session (in desired order)
allprobs="avoidland brickwall cake coverup hopper rebeldie sheep"

# For each problem foo in newprobs that has an oldkattis:foo, add foo to oldprobs
oldprobs=""


###########################################
# Do not touch remaining lines
###########################################

for prob in $allprobs; do
	/usr/local/kattis/bin/admin/addproblem.sh -a "$starttime" -o "$owner" $prob
done

for prob in $oldprobs; do
	/usr/local/kattis/bin/rejudge.sh -r "reactivate oldkattis:$prob" -Q -a -o -n $prob
done

psql kattis -c 'update session set site_id=1 where site_id=4'
psql kattis -c 'update submission set site_id=1 where site_id=4'

/usr/local/kattis/bin/admin/addsession -S 4 -n "$name" -t "$starttime" -l "$length" -r --open-registration -p $allprobs
for judge in $judges; do
    /usr/local/kattis/bin/admin/addjudge.sh -r "$name" "$judge"
done


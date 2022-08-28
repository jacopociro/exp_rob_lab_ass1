(define (problem sherlockbot_problem) (:domain sherlockbot)
(:objects 
    wp0, wp1, wp2, wp3 - waypoint
    sherlock - robot
    home - home
    oracle - oracle
)

(:init
    (move wp0 wp1)
    (move wp0 wp2)
    (move wp0 wp3)
    (move wp1 wp0)
    (move wp1 wp2)
    (move wp1 wp3)
    (move wp2 wp0)
    (move wp2 wp1)
    (move wp2 wp3)
    (move wp3 wp0)
    (move wp3 wp1)
    (move wp3 wp2)

    (visited wp0)
    (visited wp1)
    (visited wp2)
    (visited wp3)
    (robot_home home)
    (=(hypothesis_complete) 0)



)

(:goal (and
    ;todo: put the goal condition here
    (oracle_called oracle)
))

;un-comment the following line if metric is needed
;(:metric minimize (???))
)
rocky = ("rock", 100, 20,  80)
peter = ("rock", 40, 60,  60)
rockMonster = ("rock", 60, 30, 100)
paperMan = ("paper", 40, 20, 100)
paperMario = ("paper", 80, 10, 100)
gutenberg = ("paper", 20, 70, 100)
kartana = ("scissors", 130, 10,  40)
nightblood = ("scissors", 150,  0,  20)
fi = ("scissors", 20, 80,  20)


#redefining tuple variables to make code easier to understand




def attack(player1,player2):
    
    p1Type = (player1[0])
    p1Str = (player1[1])
    p1Def = (player1[2])
    p1hp_remaining = (player1[3])
    p2Type = (player2[0])
    p2Str = (player2[1])
    p2Def = (player2[2])
    hp_remaining = (player2[3])
    p1_vs_p2 = (p1Str - p2Def)
    
    def rps():
        if p1Type == p2Type:
            advantage = 1
        elif p1Type == "rock" and p2Type == "paper":
            advantage = .5
        elif p1Type == "scissors" and p2Type == "rock":
            advantage = .5  
        elif p1Type == "paper" and p2Type == "scissors":
            advantage = .5
        else: 
            advantage = 2
        return (advantage)
    
    typeEffectiveness = rps()
  

    #exception for Strength - Defense when answer is < 0
    if p1_vs_p2 < 0:
        p1_vs_p2 = 0
     
    
    hp_remaining = (hp_remaining - (p1_vs_p2) * typeEffectiveness)
    
    #exception if hp <0, hp will read as zero
    if hp_remaining < 0:
        hp_remaining = 0
        
    return hp_remaining


int winner(char ownSelection, char otherSelection)
{
    if (ownSlection == 'R') {
        if (otherSelection == 'R') {
            return 0;
        } else if (otherSelection == 'P') {
            return 2; //player 2 (other) wins
        } else if (otherSelection == 'S') {
            return 1;
        }
    } else if (ownSlection == 'P') {
        if (otherSelection == 'P') {
            return 0;
        } else if (otherSelection == 'S') {
            return 2; //player 2 (other) wins
        } else if (otherSelection == 'R') {
            return 1;
        }
    } else if (ownSlection == 'S') {
        if (otherSelection == 'S') {
            return 0;
        } else if (otherSelection == 'R') {
            return 2; //player 2 (other) wins
        } else if (otherSelection == 'P') {
            return 1;
        }
    }
}



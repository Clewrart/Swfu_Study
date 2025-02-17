package org.example;

import java.util.Random;
import java.util.Arrays;

public class Card implements Comparable<Card> {
    private ECardNumber value;
    private ECardSuit suit;

    public Card(ECardNumber value, ECardSuit suit) {
        this.value = value;
        this.suit = suit;
    }

    public Card() {

    }

    public static Card generate() {
        Random random = new Random();
        ECardNumber number = ECardNumber.values()[random.nextInt(ECardNumber.values().length)];
        ECardSuit suit = ECardSuit.values()[random.nextInt(ECardSuit.values().length)];
        return new Card(number, suit);
    }

    @Override
    public int compareTo(Card other) {
        // 根据扑克牌比较规则，先按花色顺序比较，再按点数顺序比较
        int suitComparison = Arrays.asList(ECardSuit.values()).indexOf(this.suit) - Arrays.asList(ECardSuit.values()).indexOf(other.suit);
        if (suitComparison != 0) {
            return suitComparison;
        } else {
            return Arrays.asList(ECardNumber.values()).indexOf(this.value) - Arrays.asList(ECardNumber.values()).indexOf(other.value);
        }
    }
}
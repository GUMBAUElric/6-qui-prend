<template>
  <div class="container-game-cards" v-if="partyStarted">
    <h2 class="title">Vos cartes</h2>
    <div class="row">
      <GameCard v-for="(card, index) in players[0].cards" :key="index" :number="card.number" :value="card.value" @click.native="playCard(index)"></GameCard>
    </div>
  </div>
</template>

<script>
/** Import */
import { mapState, mapActions } from 'vuex'
import GameCard from '@/components/GameCard.vue'

export default {
  name: 'PlayerCards',
  components: {
    GameCard,
  },
  computed: {
    ...mapState(['players', 'partyStarted', 'socket', 'playerCanPlay']),
  },
  methods: {
    ...mapActions(['removePlayerCard']),
    playCard(card) {
      if (!this.playerCanPlay) return

      this.socket.send(`playCard ${card + 1}`)
      this.removePlayerCard(card)
    },
  },
}
</script>

<style>
.container-game-cards {
  width: 100%;
  height: 39%;
  display: flex;
  justify-content: space-evenly;
  border-bottom: 1px solid #000;
  align-items: center;
}

.container-game-cards .title {
  height: 100%;
  min-width: 100px;
  display: flex;
  justify-content: center;
  align-items: center;
  transform: rotate(-20deg);
  font-size: 1.2rem;
}

.container-game-cards .row {
  width: 650px;
  height: 100%;
  display: flex;
  justify-content: space-evenly;
  align-items: center;
  flex-flow: wrap;
}
</style>

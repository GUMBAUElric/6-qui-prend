<template>
  <div class="container-rows" v-if="partyStarted">
    <h2 class="title">Rangées</h2>
    <div class="rows-cards">
      <div class="row">
        <GameCard v-for="(card, index) in rows[0]" :key="index" :number="card.number" :value="card.value" @click.native="chooseRow(1)"></GameCard>
      </div>
      <div class="row">
        <GameCard v-for="(card, index) in rows[1]" :key="index" :number="card.number" :value="card.value" @click.native="chooseRow(2)"></GameCard>
      </div>
      <div class="row">
        <GameCard v-for="(card, index) in rows[2]" :key="index" :number="card.number" :value="card.value" @click.native="chooseRow(3)"></GameCard>
      </div>
      <div class="row">
        <GameCard v-for="(card, index) in rows[3]" :key="index" :number="card.number" :value="card.value" @click.native="chooseRow(4)"></GameCard>
      </div>
    </div>
  </div>
</template>

<script>
/** Import */
import { mapState } from 'vuex'
import GameCard from '@/components/GameCard.vue'

export default {
  name: 'RowsCards',
  components: {
    GameCard,
  },
  computed: {
    ...mapState(['socket', 'partyStarted', 'rows', 'playerChooseRow']),
  },
  methods: {
    chooseRow(row) {
      if (!this.playerChooseRow) return
      this.socket.send(`chooseRow ${row}`)
    },
  },
}
</script>

<style>
.container-rows {
  width: 100%;
  height: 52%;
  display: flex;
  justify-content: space-evenly;
}

.container-rows .title {
  display: flex;
  justify-content: center;
  align-items: center;
  min-width: 100px;
  transform: rotate(-20deg);
  font-size: 1.2rem;
}

.container-rows .rows-cards {
  width: 650px;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
}

.container-rows .rows-cards .row {
  width: 100%;
  height: 100%;
  display: flex;
  justify-content: flex-start;
  align-items: center;
  flex-flow: wrap;
}
</style>

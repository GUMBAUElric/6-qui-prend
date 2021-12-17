<template>
  <div class="game-card">
    <div class="game-card__header">{{ number }}</div>
    <div class="game-card__body">
      <img v-for="(index, item) in value" :key="item" src="../assets/game-logo.png" alt="logo-6-qui-prend" />
    </div>
  </div>
</template>

<script>
export default {
  name: 'GameCard',
  props: {
    number: {
      type: Number,
      default: 0,
    },
    value: {
      type: Number,
      default: 0,
    },
  },
}
</script>

<style>
.game-card {
  width: 70px;
  height: 70px;
  background-color: #fff;
  border-radius: 0.5rem;
  box-shadow: rgba(0, 0, 0, 0.24) 0px 3px 8px;
  padding: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  position: relative;
  margin: 0 20px;
  transition: all 300ms ease;
  cursor: pointer;
}

.game-card:hover {
  transform: translateY(-10px);
}

.game-card__header {
  width: 100%;
  height: 60%;
  display: flex;
  justify-content: center;
  align-items: center;
}

.game-card__body {
  width: 100%;
  height: 40%;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-flow: wrap;
}

.game-card__body img {
  width: 13px;
  margin: 0 2px;
}
</style>

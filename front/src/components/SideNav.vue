<template>
  <div class="sidenav">
    <button v-if="!partyStarted" class="btn" @click="setReady" :class="ready.isReady ? 'btn--red' : 'btn--green'">{{ ready.msg }}</button>
    <p v-if="coutdown" class="countdown-status">Début de la partie dans {{ time }} secondes</p>
    <p v-if="countDownTour" class="countdown-status">Tour terminé, nouveau tour dans {{ time }} secondes</p>
    <p v-if="countDownRound" class="countdown-status">Manche terminée, nouvelle manche dans {{ time }} secondes</p>
    <p v-if="partyStarted && !countDownTour && !countDownRound" class="title">C'est parti !</p>
  </div>
</template>

<script>
/** Import */
import { mapState } from 'vuex'

export default {
  name: 'SideNav',
  data() {
    return {
      ready: {
        isReady: false,
        msg: 'Prêt',
      },
      time: 0,
      interval: null,
    }
  },
  watch: {
    coutdown(start) {
      if (start) this.startCountDown(10)
      else {
        clearInterval(this.interval)
        this.time = 0
      }
    },
    countDownTour(start) {
      if (start) this.startCountDown(10)
      else {
        clearInterval(this.interval)
        this.time = 0
      }
    },
    countDownRound(start) {
      if (start) this.startCountDown(10)
      else {
        clearInterval(this.interval)
        this.time = 0
      }
    },
    partyStarted(start) {
      if (start) {
        this.ready.isReady = false
        this.ready.msg = 'Prêt'
      }
    },
  },
  computed: {
    ...mapState(['socket', 'coutdown', 'countDownTour', 'countDownRound', 'partyStarted']),
  },
  methods: {
    setReady() {
      this.ready.isReady = !this.ready.isReady
      this.ready.msg = this.ready.isReady ? 'Pas prêt' : 'Prêt'
      this.socket.send(`setReady ${Number(this.ready.isReady)}`)
    },
    startCountDown(time) {
      this.time = time
      this.interval = setInterval(() => {
        if (this.time !== 0) {
          this.time -= 1
          return
        }

        clearInterval(this.interval)
        this.time = 0
      }, 1000)
    },
  },
}
</script>

<style>
.sidenav {
  width: 100%;
  height: 70px;
  display: flex;
  box-shadow: rgba(50, 50, 93, 0.25) 0px 2px 5px -1px, rgba(0, 0, 0, 0.3) 0px 1px 3px -1px;
  align-items: center;
}

.sidenav .btn {
  margin: 35px 0 0 25px;
  transform: translateY(-50%);
  width: 100px;
  border-radius: 0.5rem;
  color: #fff;
  padding: 7px;
  cursor: pointer;
  transition: background-color 300ms ease;
}

.sidenav .btn--green {
  background-color: #2cbc63;
}

.sidenav .btn--red {
  background-color: red;
}

.sidenav .countdown-status {
  margin-left: 15px;
  font-size: 0.9rem;
}

.sidenav .title {
  margin-left: 15px;
}
</style>

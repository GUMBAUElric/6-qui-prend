import Vue from 'vue'
import Vuex from 'vuex'
import router from '@/router/index'

const { ipcRenderer } = require('electron')

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    socket: {
      send: (msg, event = 'message-from-browser') => {
        ipcRenderer.send(event, msg)
      },
    },
    players: [],
    playersScore: [],
    coutdown: false,
    countDownTour: false,
    countDownRound: false,
    partyStarted: false,
    displayModal: false,
    playerCanPlay: false,
    playerChooseRow: false,
    rows: [[], [], [], []],
  },
  mutations: {
    SET_PLAYER(state, { uid, name }) {
      state.players = [...state.players, { uid, name, status: 'non prêt', cards: [], points: 0 }]
    },
    REMOVE_PLAYER(state, { uid }) {
      state.players = state.players.filter((item) => item.uid !== uid)
    },
    SET_PLAYER_CAN_PLAY(state, canPlay) {
      state.playerCanPlay = canPlay
    },
    SET_PLAYER_STATUS(state, { uid, status }) {
      state.players.forEach((player) => {
        if (player.uid === uid) player.status = status
      })
    },
    SET_PLAYERS_STATUS(state, status) {
      state.players.forEach((player) => {
        player.status = status
      })
    },
    SET_COUNTDOWN(state, countdown) {
      state.coutdown = countdown
    },
    SET_COUNTDOWN_TOUR(state, countdown) {
      state.countDownTour = countdown
    },
    SET_COUNTDOWN_ROUND(state, countdown) {
      state.countDownRound = countdown
    },
    SET_PARTY_STARTED(state, started) {
      state.partyStarted = started
    },
    SET_PLAYER_CARDS(state, cards) {
      state.players.forEach((player) => {
        if (player.uid === cards[0].belongsTo) {
          player.cards = cards
        }
      })
    },
    REMOVE_PLAYER_CARD(state, card) {
      state.players[0].cards.splice(card, 1)
    },
    SET_ROWS(state, rows) {
      state.rows = state.rows.map((row, index) => {
        row = rows[index]
        return row
      })
    },
    SET_PLAYER_CHOOSE_ROW(state, row) {
      state.playerChooseRow = row
    },
    SET_PLAYERS_POINTS(state, { uid, points }) {
      state.players.forEach((player) => {
        if (player.uid === uid) player.points = points
      })
    },
    DISPLAY_MODAL(state, display) {
      state.displayModal = display
    },
    SET_PLAYERS_SCORE(state) {
      state.playersScore = [...state.players]
      state.playersScore.sort((a, b) => {
        if (a.points < b.points) return -1
        if (a.points > b.points) return 1
        return 0
      })
    },
    RESET_PLAYER_POINTS(state) {
      state.players.forEach((player) => {
        player.points = 0
      })
    },
  },
  actions: {
    listenSocketMsg({ state, commit }) {
      ipcRenderer.on('message-from-socket', (event, data) => {
        const { type, message } = JSON.parse(data)
        console.log(data)

        // Set the player name
        if (type === 'nameSet') {
          commit('SET_PLAYER', message[0])
          router.push({ path: '/home' })
          return
        }

        // Get opponents players
        if (type === 'newPlayer' || type === 'playersConnected') {
          message.forEach((player) => commit('SET_PLAYER', player))
          return
        }

        // Opponents player left
        if (type === 'playerExit') {
          commit('REMOVE_PLAYER', message[0])
          return
        }

        // Player ready
        if (type === 'isReady') {
          if (message === '1') commit('SET_PLAYER_STATUS', { uid: state.players[0].uid, status: 'Prêt' })
          else commit('SET_PLAYER_STATUS', { uid: state.players[0].uid, status: 'Pas prêt' })
          return
        }

        // Opponent player ready
        if (type === 'playerReady') {
          commit('SET_PLAYER_STATUS', { uid: message, status: 'Prêt' })
          return
        }

        // Opponent player not ready
        if (type === 'playerNotReady') {
          commit('SET_PLAYER_STATUS', { uid: message, status: 'Pas prêt' })
          return
        }

        // Handle countdown
        if (type === 'countDown') {
          if (message === '1') commit('SET_COUNTDOWN', true)
          else commit('SET_COUNTDOWN', false)
          return
        }

        // Show rows
        if (type === 'showRows') {
          commit('SET_PARTY_STARTED', true)
          commit('SET_COUNTDOWN', false)
          commit('SET_COUNTDOWN_TOUR', false)
          commit('SET_COUNTDOWN_ROUND', false)
          commit('SET_ROWS', message)
          return
        }

        // Show player cards
        if (type === 'showCards') {
          commit('SET_PLAYER_CARDS', message)
          commit('SET_PLAYERS_STATUS', 'Choisit une carte')
          commit('SET_PLAYER_CAN_PLAY', true)
          return
        }

        // Player play his card
        if (type === 'cardRemoved') {
          commit('SET_PLAYER_CAN_PLAY', false)
          commit('SET_PLAYER_STATUS', { uid: state.players[0].uid, status: 'A joué sa carte' })
          return
        }

        // Opponent player play
        if (type === 'playerPlayed') {
          commit('SET_PLAYER_STATUS', { uid: message, status: 'A joué sa carte' })
          return
        }

        // Show the deck round
        if (type === 'showDeckRound') {
          message.forEach((card) => {
            commit('SET_PLAYER_STATUS', { uid: card.belongsTo, status: `A joué la carte ${card.number}` })
          })
          commit('SET_COUNTDOWN_TOUR', true)
          return
        }

        // Player choose row
        if (type === 'chooseRow') {
          if (message === '1') {
            commit('SET_PLAYER_STATUS', { uid: state.players[0].uid, status: 'Veuillez choisir une rangée' })
            commit('SET_PLAYER_CHOOSE_ROW', true)
            commit('SET_COUNTDOWN_TOUR', false)
          } else {
            commit('SET_PLAYER_CHOOSE_ROW', false)
            commit('SET_COUNTDOWN_TOUR', true)
          }
          return
        }

        // Oppoenent player choose a row
        if (type === 'playerChooseRow') {
          commit('SET_PLAYER_STATUS', { uid: message, status: 'Choisit une rangée' })
          commit('SET_COUNTDOWN_TOUR', false)
          return
        }

        // Oppoenent player has choose a row
        if (type === 'playerHasChoosenRow') {
          commit('SET_PLAYER_STATUS', { uid: message, status: 'A choisit une rangée' })
          commit('SET_COUNTDOWN_TOUR', true)
          return
        }

        // New round
        if (type === 'newRound') {
          commit('SET_COUNTDOWN_ROUND', true)
          return
        }

        // Show user points
        if (type === 'showPoints') {
          message.forEach(({ uid, points }) => {
            commit('SET_PLAYERS_POINTS', { uid, points })
          })
          return
        }

        // End game
        if (type === 'endGame') {
          commit('SET_COUNTDOWN_TOUR', false)
          return
        }

        // Show user points when game is finish
        if (type === 'playersPoint') {
          message.forEach(({ uid, points }) => {
            commit('SET_PLAYERS_POINTS', { uid, points })
          })
          commit('SET_PLAYERS_SCORE')
          commit('DISPLAY_MODAL', true)
          commit('SET_PARTY_STARTED', false)
        }
      })
    },
    removePlayerCard({ commit }, card) {
      commit('REMOVE_PLAYER_CARD', card)
    },
    closeModal({ commit }) {
      commit('DISPLAY_MODAL', false)
      commit('RESET_PLAYER_POINTS')
    },
  },
})

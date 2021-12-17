<template>
  <div class="sidebar">
    <div class="sidebar__title">
      <h2>Joueurs</h2>
    </div>
    <div class="sidebar__content">
      <div class="user" v-for="player in players" :key="player.uid">
        <div class="user__avatar">
          <img :src="`https://avatars.dicebear.com/api/adventurer-neutral/${player.name}.svg`" alt="user-avatar" />
        </div>
        <div class="user__infos">
          <h3>{{ player.name }}</h3>
          <p>{{ player.status }}</p>
        </div>
        <div class="user__points">
          <p>{{ player.points }}</p>
        </div>
      </div>
    </div>
    <div class="sidebar__footer">
      <button class="btn" @click="exit">Quitter</button>
    </div>
  </div>
</template>

<script>
/** Import */
import { mapState } from 'vuex'

export default {
  name: 'SideBar',
  computed: {
    ...mapState(['socket', 'players']),
  },
  methods: {
    exit() {
      this.socket.send('EXIT 1')
      this.socket.send('', 'exit-app')
    },
  },
}
</script>

<style>
.sidebar {
  width: 100%;
  height: 100%;
  background-color: var(--primary-color);
  box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
}

.sidebar .sidebar__title {
  width: 100%;
  height: 10%;
  display: flex;
  justify-content: center;
  align-items: center;
  color: #fff;
}

.sidebar .sidebar__title h2 {
  font-size: 1.2rem;
}

.sidebar .sidebar__content {
  width: 100%;
  height: 84%;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  flex: 1;
}

.sidebar .sidebar__content .user {
  width: 90%;
  height: 90px;
  display: flex;
  align-content: center;
  justify-content: center;
  position: relative;
}

.sidebar .sidebar__content .user .user__avatar {
  width: 30%;
  display: flex;
  justify-content: center;
  align-content: center;
}

.sidebar .sidebar__content .user .user__infos {
  width: 70%;
  color: #fff;
  margin-left: 15px;
  display: flex;
  justify-content: center;
  align-content: center;
  flex-direction: column;
}

.sidebar .sidebar__content .user .user__infos p {
  margin-top: -10px;
  font-size: 0.8rem;
}

.sidebar .sidebar__content .user .user__points {
  width: 22px;
  height: 22px;
  display: flex;
  justify-content: center;
  align-items: center;
  background-color: #2cbc63;
  border-radius: 2rem;
  position: absolute;
  left: -5px;
  top: 5px;
}

.sidebar .sidebar__content .user .user__points p {
  font-size: 0.8rem;
}

.sidebar .sidebar__footer {
  height: 6%;
  display: flex;
  justify-content: center;
  align-content: center;
}

.sidebar .sidebar__footer .btn {
  margin: 10px 0 10px 0;
  width: 75px;
  background-color: #fff;
  border-radius: 0.5rem;
  color: #000;
  cursor: pointer;
}
</style>

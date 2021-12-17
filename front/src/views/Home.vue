<template>
  <div class="container">
    <Modal v-if="displayModal" @close="closeModal"></Modal>
    <div class="left">
      <SideBar></SideBar>
    </div>
    <div class="right">
      <SideNav></SideNav>
      <PlayerCards></PlayerCards>
      <RowsCards></RowsCards>
    </div>
  </div>
</template>

<script>
/** Import */
import { mapState, mapActions } from 'vuex'
import SideBar from '@/components/SideBar.vue'
import SideNav from '@/components/SideNav.vue'
import PlayerCards from '@/components/PlayerCards.vue'
import RowsCards from '@/components/RowsCards.vue'
import Modal from '@/components/Modal.vue'

export default {
  name: 'Home',
  components: {
    SideBar,
    SideNav,
    PlayerCards,
    RowsCards,
    Modal,
  },
  computed: {
    ...mapState(['player', 'displayModal']),
  },
  methods: {
    ...mapActions(['closeModal']),
  },
}
</script>

<style>
.container {
  width: 100%;
  height: 100%;
  position: relative;
  display: flex;
}

.container .left {
  height: 100vh;
  min-width: 200px;
  display: flex;
  justify-content: flex-end;
  align-items: flex-end;
}

.container .right {
  width: 100%;
}

.container .cards {
  width: 100%;
}
</style>

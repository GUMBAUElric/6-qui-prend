<template>
  <div id="app">
    <router-view />
  </div>
</template>

<script>
/** Import */
import { mapActions } from 'vuex'

export default {
  name: 'Home',
  methods: {
    ...mapActions(['listenSocketMsg']),
  },
  mounted() {
    // Listen message from socket server
    this.listenSocketMsg()
  },
}
</script>

<style></style>

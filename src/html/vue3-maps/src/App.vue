<template>
  <div class="d-flex text-center" style="height: 20vh">
    <div class="m-auto">
      <h4>Your Position</h4>
      Latitude: {{currPos.lat.toFixed(2)}}, Longitude: {{currPos.lng.toFixed(2)}}
    </div>
    <div class="m-auto">
      <h4>Clicked Position</h4>
      <span v-if="otherPos">
        Latitude: {{ otherPos.lat.toFixed(2)}}, Longitude:
        {{ otherPos.lng.toFixed(2)}}
      </span>
    </div>
  </div>
  <div ref="mapDiv" style="width:100%; height:80vh" />
</template>

<script>

import { computed, onMounted, onUnmounted, ref, watch } from 'vue'
import { useGeolocation } from './useGeolocation'
import { Loader} from '@googlemaps/js-api-loader'

const GOOGLE_MAPS_API_KEY = ''

export default {
  name: 'App',
  setup() {
    const { coords } = useGeolocation()
    const currPos = computed(() => ({
      lat: coords.value.latitude,
      lng: coords.value.longitude
    }))

    const otherPos = ref(null)
    const loader = new Loader({apiKey: GOOGLE_MAPS_API_KEY})
    const mapDiv = ref(null)
    let map = ref(null)
    let clickListener = null

    onMounted(async () => {
      await loader.load()
      map.value = new google.maps.Map(mapDiv.value, {
        center: currPos.value,
        zoom: 7
      })
      clickListener = map.value.addListener(
        'click',
        ({latLng: {lat, lng}}) =>
        (otherPos.value = {lat: lat(), lng: lng()})
      )
    })
    onUnmounted(async () => {
      if(clickListener) clickListener.remove()
    })

    let line = null
    watch([map, currPos, otherPos], () => {
      if(line) line.setMap(null)
      if(map.value && otherPos.value != null)
        line = new google.maps.Polyline({
          path: [currPos.value, otherPos.value],
          map: map.value
        })
    })
    return {currPos, otherPos, mapDiv}
  }
}
</script>


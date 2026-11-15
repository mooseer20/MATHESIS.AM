import { Moon, Search, Sun } from 'lucide-react';

export default function Topbar() {
  return (
    <header className="topbar">
      <div className="logo"><span className="logo-mark">M</span>Mathesis jan</div>
      <nav className="top-links"><span>Լուծել</span><span>Սովորել</span><span>Պատկերել</span></nav>
      <div className="search"><span>Մուտքագրեք խնդիրը… (օր.՝ սահման, ինտեգրալ, ածանցյալ)</span><Search size={18} /></div>
      <div className="toggle"><Sun size={18} /><Moon size={18} /></div>
      <div className="avatar" />
    </header>
  );
}
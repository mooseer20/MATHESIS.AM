const  it  = [  ' Solver ' , 'Mathemaics' , 'Vizu' , 'Prak' , 'PAtm']; 

export default function Sidebar() {

    return (
        <aside className="sidebar">
          {it.map((label, i) => (
            <div key={label} className={i === 0 ? 'nav-item active' : 'nav-item'}>{label}</div>
          ))}
        </aside>
      );
    }